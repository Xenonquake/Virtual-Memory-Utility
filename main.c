#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

// Process information structure
typedef struct {
    pid_t pid;
    char name[16];
    size_t vm_size;
} ProcessInfo;

// Comparison function for qsort (descending order by vm_size)
int compare_process(const void *a, const void *b) {
    const ProcessInfo *p1 = (const ProcessInfo *)a;
    const ProcessInfo *p2 = (const ProcessInfo *)b;
    if (p1->vm_size > p2->vm_size) return -1;
    if (p1->vm_size < p2->vm_size) return 1;
    return 0;
}

// Function to read process information from /proc/[pid]/status
[[nodiscard]] int get_process_info(const char *pid_str, ProcessInfo *proc_info) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%s/status", pid_str);

    FILE *status_file = fopen(path, "r");
    if (!status_file) {
        return 1; // Skip if unavailable (e.g., process ended or permission denied)
    }

    char line[256];
    char proc_name[16] = "";
    size_t vm_size = 0;

    // Read Name and VmSize
    while (fgets(line, sizeof(line), status_file)) {
        if (strncmp(line, "Name:", 5) == 0) {
            sscanf(line, "Name:\t%15s", proc_name);
        } else if (strncmp(line, "VmSize:", 7) == 0) {
            sscanf(line, "VmSize:\t%zu kB", &vm_size);
            break; // Stop once we have VmSize
        }
    }
    fclose(status_file);

    // If we got both name and vm_size, add to struct
    if (proc_name[0] && vm_size > 0) {
        proc_info->pid = atoi(pid_str);
        strncpy(proc_info->name, proc_name, sizeof(proc_info->name) - 1);
        proc_info->name[sizeof(proc_info->name) - 1] = '\0';
        proc_info->vm_size = vm_size;
        return 0;
    }

    return 1;
}

// Function to print process information
void print_process_info(const ProcessInfo *processes, size_t count) {
    printf("PID\tNAME\t\t\tVMSIZE (kB)\n");
    printf("-----------------------------------------\n");
    for (size_t i = 0; i < 10 && i < count; i++) {
        printf("%d\t%-15s\t%zu\n", processes[i].pid, processes[i].name, processes[i].vm_size);
    }
}

// Main function
int main() {
    // Initialize dynamic array
    size_t capacity = 100;
    size_t count = 0;
    ProcessInfo *processes = malloc(capacity * sizeof(ProcessInfo));
    if (!processes) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Open /proc directory
    DIR *proc_dir = opendir("/proc");
    if (!proc_dir) {
        perror("Cannot open /proc");
        free(processes);
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(proc_dir)) != NULL) {
        // Check if the entry name is purely numeric (indicating a PID)
        if (strspn(entry->d_name, "0123456789") == strlen(entry->d_name)) {
            // Resize array if full
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

            // Get process information
            if (get_process_info(entry->d_name, &processes[count]) == 0) {
                count++;
            }
        }
    }
    closedir(proc_dir);

    // Sort processes by vm_size
    qsort(processes, count, sizeof(ProcessInfo), compare_process);

    // Print top ten processes
    print_process_info(processes, count);

    // Clean up
    free(processes);
    return 0;
}
