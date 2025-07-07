#include <stdio.h>
unsigned long long simpleHash(const char *str) {
    unsigned long long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; 

    return hash;
}
int main() {
    char password[100];
    printf("Enter your password to generate hash: ");
    fgets(password, sizeof(password), stdin);
    int i = 0;
    while (password[i] != '\0') {
        if (password[i] == '\n') password[i] = '\0';
        i++;
    }
    unsigned long long hashed = simpleHash(password);
    printf("The hash of your password is: %llu\n", hashed);
    return 0;
}