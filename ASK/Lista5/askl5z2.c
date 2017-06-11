long puzzle2(char* s, char* d){ char cl;
    for (char* res = s; 1; res++) {
L3:     // char* r8 = res + 1;
        // char r9 = *res;  // *(r8 - 1);
        char* i = d;
L2:     do {
            i++;
            cl = *(i - 1);

            if (cl == 0)
L7:             return res - s;
        } while (*res != cl);  // if (r9 != cl) goto L2;
        // res++;  //res = r8;
    } // goto L3;
}
