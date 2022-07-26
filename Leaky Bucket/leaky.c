#include<stdio.h>

int main() {
    int incoming, outgoing, buck_size, n, store = 0, i;
    printf("Enter Bucket Size, Outgoing Rate and Number of Packets: ");
    scanf("%d%d%d", &buck_size, &outgoing, &n);
    for(i = 0; i < n; i++) {
        printf("Enter Incoming Size: ");
        scanf("%d", &incoming);
        if(incoming <= buck_size - store) {
            store += incoming;
            printf("Bucket Buffer Size %d out of %d\n", store, buck_size);
        } else {
            printf("Dropped %d No of Packets!\n", (incoming-(buck_size-store)));
            store = buck_size;
        }
        store -= outgoing;
        printf("After Outgoing Buffer Size %d out of %d\n", store, buck_size);
    }
    return 0;
}