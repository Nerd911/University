union elem {
    struct { // 16B
        long*p; // 8B
        long y;  // 8B
    } e1;
    struct { // 16B
        long x; // 8B
        union elem*next; // 8B bo wskaźnik
    } e2;
};
/*
? proc(? arg){
    rax  = arg->next;       // arg->y // *(arg + 8)
    rdx  = *(arg->next);    // arg->next->p
    rdx  = *(arg->next->p); // typu long
    rdx -= *(rax + 8)       // arg->next->y
 // rdx  = *(arg->next->p) - *(rax       + 8)
 // rdx  = *(arg->next->p) - *(arg->next + 8)
 // rdx  = *(arg->next->p) -   arg->next->y
    arg->x = *(arg->next->p) -   arg->next->y;
}

elem* proc(elem* e){
    e->e2.x = *(e->e2.next->e1.p) - e->e2.next->e1.y;
    return e->e2.next;
}
*?
