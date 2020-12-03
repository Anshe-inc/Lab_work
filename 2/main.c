#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char surname[64];
    size_t group;
    size_t id;
    size_t scholarship;
} pupil;

void print(pupil *a);
int read(pupil * a);
int read_arr (pupil ** a);

int cmp(void * a, void * b) {
    pupil *fir = (pupil *)a;
    pupil *sec = (pupil *)b;
    
    return (fir->id) - (sec->id);
}

int main () {
    
    pupil *p;
    size_t size = read_arr(&p);
    qsort(p, size, sizeof(pupil), cmp);
    for (size_t i = 0; i < size; i++) {
        print(p + i);
        printf("\n");
    }

    free(p);
    return 0;
}

void print(pupil *a) {
    if (a == NULL) {
        printf("NULL\n");
        return;        
    }
    printf("Surname:\t %s\n", a->surname);
    printf("Group #:\t %lu\n", a->group);
    printf("ID:\t\t %lu\n", a->id);
    printf("Scholarsh.:\t %lu\n", a->scholarship);	
}
int read(pupil * a) {
    int res = 0;
    if((scanf("%63s", &(a->surname))) > 0) 
        ++res;
    if((scanf("%lu", &(a->group))) > 0)
        ++res;
    if((scanf("%lu", &(a->id))) > 0) 
        ++res;
    if((scanf("%lu", &(a->scholarship))) > 0) 
        ++res;
    return res;
}

int read_arr (pupil ** a) {
    size_t size = 1;
    *a = (pupil *)malloc(sizeof(pupil));
    unsigned int i = 0, c;
    for (i = 0; (c = read(*a + i)); ++i) {
        //printf("%d\n", c);
    	if (size <= i + 1) {
    	    size *= 2;
    	    *a = realloc(*a, size * sizeof(pupil));
    	}
    	if (c != 4) {
    	    if (i == 0)
    	        continue;
    	    --i;
    	}
    }
    if (i == 0) {
    	printf("NO INFO");
    	return 0;
    }else {
    	*a = realloc(*a, i * sizeof(*a));
    }
    return i;
}
