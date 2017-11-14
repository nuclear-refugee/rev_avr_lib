#include "../rev_DEVICE.h"
#include "../rev_serial.h"

int main() {
    rev_serial_init();

    printf("Hello world \n");
    printf("Serial test 2017.11.04\n");

    char s[20];
    scanf("%s", s);
    printf("input s: %s\n", s);
    
    return 0;
}
