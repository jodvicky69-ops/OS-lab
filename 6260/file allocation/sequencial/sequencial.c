#include <stdio.h>
int main() {
 printf("Roll no: 25071A6260\n");
 int disk[50] = {0}, start, len, alloc = 1;
 printf("Enter start block and length of file: ");
 scanf("%d %d", &start, &len);
 for (int i = start; i < start + len; i++) if (disk[i]) alloc = 0;
 if (alloc) {
 printf("File allocated successfully. Blocks: ");
 for (int i = start; i < start + len; i++) {
 disk[i] = 1; printf("%d ", i);
 }
 printf("\n");
 } else printf("Allocation failed: Contiguous blocks unavailable.\n");
 return 0;
}
