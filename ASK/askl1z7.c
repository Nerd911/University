void insertion_sort(int arr[], int length) {
  int j, temp;
  for (int i = 0; i < length; i++) {
    j = i;
    while (j > 0 && arr[j] < arr[j-1]) {
      temp = arr[j];
      arr[j] = arr[j-1];
      arr[j-1] = temp;
      j--;
    }
  }
}

void insertion_sort(int arr[], int length) {
  int j, temp;
  int i = 0;

  bool b;
  beginloop1:
  b = !(i < length);
  if b goto endloop1;

    j = i;
    beginloop2:
    b = !(j > 0 && arr[j] < arr[j-1]);
    if b goto endloop2;
      temp = arr[j];
      arr[j] = arr[j-1];
      arr[j-1] = temp;
      j--;
    goto beginloop2;
    endloop2;
    i++;
  goto beginloop1;
  endloop1:
}
