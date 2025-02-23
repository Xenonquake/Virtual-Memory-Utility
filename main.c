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

int main() {
    // Initialize dynamic array
    size_t capacity = 100;
    size_t count = 0;
    ProcessInfo *processes = malloc(capacity * sizeof(ProcessInfo));
    if (!processes) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Open /proc directory
    DIR *proc_dir = opendir("/proc");
    if (!proc_dir) {
        perror("Cannot open /proc");
        free(processes);
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(proc_dir)) != NULL) {
        // Check if the entry is a directory with a numeric name (PID)
        if (entry->d_type == DT_DIR && strspn(entry->d_name, "0123456789") == strlen(entry->d_name)) {
            // Resize array if full
            if (count == capacity) {
                capacity *= 2;
                ProcessInfo *temp = realloc(processes, capacity * sizeof(ProcessInfo));
                if (!temp) {
                    perror("Failed to reallocate memory");
                    closedir(proc_dir);
                    free(processes);
                    return 1;
                }
                processes = temp;
            }

            // Construct path to status file
            char path[256];
            snprintf(path, sizeof(path), "/proc/%s/status", entry->d_name);

            // Open status file
            FILE *status_file = fopen(path, "r");
            if (!status_file) {
                continue; // Skip if unavailable
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

            // If we got both name and vm_size, add to array
            if (proc_name[0] && vm_size > 0) {
                processes[count].pid = atoi(entry->d_name);
                strncpy(processes[count].name, proc_name, sizeof(processes[count].name) - 1);
                processes[count].name[sizeof(processes[count].name) - 1] = '\0';
                processes[count].vm_size = vm_size;
                count++;
            }
        }
    }
    closedir(proc_dir);

    // Sort processes by vm_size
    qsort(processes, count, sizeof(ProcessInfo), compare_process);

    // Display top ten processes
    printf("PID\tNAME\t\tVMSIZE (kB)\n");
    printf("---------------------------------\n");
    for (size_t i = 0; i < 10 && i < count; i++) {
        printf("%d\t%-15s\t%zu\n", processes[i].pid, processes[i].name, processes[i].vm_size);
    }

    // Clean up
    free(processes);
    return 0;
}
