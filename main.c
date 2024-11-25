#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

void test_single_line(void)
{
    int fd = open("test_single_line.txt", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open test_single_line.txt");
        return;
    }
    char *line = get_next_line(fd);
    if (line) {
        printf("Test 1 - Single line: %s\n", line);
        free(line);
    } else {
        printf("Test 1 - No line read or error.\n");
    }
    close(fd);
}

void test_multiple_lines(void)
{
    int fd = open("test_multiple_lines.txt", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open test_multiple_lines.txt");
        return;
    }
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Test 2 - Multiple lines: %s\n", line);
        free(line);
    }
    close(fd);
}

void test_empty_file(void)
{
    int fd = open("test_empty_file.txt", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open test_empty_file.txt");
        return;
    }
    char *line = get_next_line(fd);
    if (line) {
        printf("Test 3 - Empty file: %s\n", line);
        free(line);
    } else {
        printf("Test 3 - No content or error.\n");
    }
    close(fd);
}

void test_file_with_empty_lines(void)
{
    int fd = open("test_file_with_empty_lines.txt", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open test_file_with_empty_lines.txt");
        return;
    }
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Test 4 - File with empty lines: %s\n", line);
        free(line);
    }
    close(fd);
}

void test_file_with_special_characters(void)
{
    int fd = open("test_file_with_special_characters.txt", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open test_file_with_special_characters.txt");
        return;
    }
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Test 5 - File with special characters: %s\n", line);
        free(line);
    }
    close(fd);
}

void test_large_file(void)
{
    int fd = open("test_large_file.txt", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open test_large_file.txt");
        return;
    }
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);  // Just consume lines to test performance
    }
    close(fd);
}

void test_file_with_no_newline_at_end(void)
{
    int fd = open("test_file_no_newline.txt", O_RDONLY);
    if (fd == -1) {
        perror("Failed to open test_file_no_newline.txt");
        return;
    }
    char *line = get_next_line(fd);
    if (line) {
        printf("Test 6 - No newline at the end: %s\n", line);
        free(line);
    } else {
        printf("Test 6 - No content or error.\n");
    }
    close(fd);
}

void test_stdin_input(void)
{
    printf("Test 7 - Reading from stdin (Enter 'Hello World' and press Enter, then Ctrl+D to end):\n");
    char *line;
    while ((line = get_next_line(0)) != NULL) {
        printf("Stdin input: %s\n", line);
        free(line);
    }
}

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    printf("%s", get_next_line(fd));
    close(fd);  // Fermer le fichier après utilisation
    return 0;
}

