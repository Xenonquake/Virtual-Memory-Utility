#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdbool.h>
#include <getopt.h>

#define NAME_SIZE 16
#define PATH_SIZE 256
#define LINE_SIZE 256
#define INITIAL_CAPACITY 100

typedef enum {
    QUIET = 0,
    NORMAL = 1,
    VERBOSE = 2,
    DEBUG = 3
} VerbosityLevel;

// Memory formatting
[[nodiscard]] static char* format_memory_size(size_t size_kb) {
    static char buffer[32];
    const double kb = size_kb;
    const double mb = kb / 1024.0;
    const double gb = mb / 1024.0;

    if (gb >= 1.0) {
        snprintf(buffer, sizeof(buffer), "%.2f GB", gb);
    } else if (mb >= 1.0) {
        snprintf(buffer, sizeof(buffer), "%.2f MB", mb);
    } else {
        snprintf(buffer, sizeof(buffer), "%.2f KB", kb);
    }
    return buffer;
}

typedef struct {
    pid_t pid;
    char name[NAME_SIZE];
    size_t vm_size;
} ProcessInfo;

int compare_process(const void *a, const void *b) {
    const ProcessInfo *p1 = (const ProcessInfo *)a;
    const ProcessInfo *p2 = (const ProcessInfo *)b;
    return (p1->vm_size > p2->vm_size) ? -1 : (p1->vm_size < p2->vm_size) ? 1 : 0;
}

[[nodiscard]] int get_process_info(const char *pid_str, ProcessInfo *proc_info, bool debug) {
    char path[PATH_SIZE];
    snprintf(path, sizeof(path), "/proc/%s/status", pid_str);

    FILE *status_file = fopen(path, "r");
    if (!status_file) {
        return 1; // Skip if unavailable
    }

    char line[LINE_SIZE];
    char proc_name[NAME_SIZE] = "";
    size_t vm_size = 0;

    while (fgets(line, sizeof(line), status_file)) {
        if (strncmp(line, "Name:", 5) == 0) {
            sscanf(line, "Name:\t%15s", proc_name);
        } else if (strncmp(line, "VmSize:", 7) == 0) {
            sscanf(line, "VmSize:\t%zu kB", &vm_size);
            break;
        }
    }
    fclose(status_file);

    if (proc_name[0] && vm_size > 0) {
        proc_info->pid = atoi(pid_str);
        strncpy(proc_info->name, proc_name, sizeof(proc_info->name) - 1);
        proc_info->name[sizeof(proc_info->name) - 1] = '\0';
        proc_info->vm_size = vm_size;

        if (debug) {
            printf("Debug: PID=%d, Name=%s, VmSize=%zu kB\n", proc_info->pid, proc_info->name, proc_info->vm_size);
        }

        return 0;
    }
    return 1;
}

void print_process_info(const ProcessInfo *processes, size_t count, VerbosityLevel verbosity) {
    printf("PID\tNAME\t\t\tVMSIZE\n");
    printf("-----------------------------------------\n");
    for (size_t i = 0; i < 10 && i < count; i++) {
        printf("%d\t%-15s\t%s", 
               processes[i].pid, 
               processes[i].name, 
               format_memory_size(processes[i].vm_size));
        
        if (verbosity >= VERBOSE) {
            printf(" (%zu KB)", processes[i].vm_size);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    bool debug = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--debug") == 0) {
            debug = true;
        }
    }

    size_t capacity = INITIAL_CAPACITY;
    size_t count = 0;
    ProcessInfo *processes = malloc(capacity * sizeof(ProcessInfo));
    if (!processes) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    DIR *proc_dir = opendir("/proc");
    if (!proc_dir) {
        perror("Cannot open /proc");
        free(processes);
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(proc_dir)) != nullptr) {
        if (strspn(entry->d_name, "0123456789") == strlen(entry->d_name)) {
            if (count == capacity) {
                capacity *= 2;
                ProcessInfo *temp = realloc(processes, capacity * sizeof(ProcessInfo));
                if (!temp) {
                    perror("Failed to reallocate memory");
                    closedir(proc_dir);
                    free(processes);
                    exit(EXIT_FAILURE);
                }
                processes = temp;
            }

            if (get_process_info(entry->d_name, &processes[count], debug) == 0) {
                count++;
            }
        }
    }
    closedir(proc_dir);

    qsort(processes, count, sizeof(ProcessInfo), compare_process);

    print_process_info(processes, count);

    free(processes);
    return 0;
}
