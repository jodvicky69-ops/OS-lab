#include <stdio.h>
int main() {
 printf("Roll no: 25071A6260\n");
 int disk[50] = {0}, n, b[20], alloc = 1;
 printf("Enter number of blocks and block sequence: "); scanf("%d", &n);
 for (int i = 0; i < n; i++) scanf("%d", &b[i]);
 for (int i = 0; i < n; i++) if (disk[b[i]]) alloc = 0;
 if (alloc) {
 printf("Linked Allocation Sequence: ");
 for (int i = 0; i < n; i++) {
 disk[b[i]] = 1; printf("%d -> ", b[i]);
 }
 printf("NULL\nFile allocated successfully.\n");
 } else printf("Allocation failed: One or more blocks already allocated.\n");
 return 0;
}
