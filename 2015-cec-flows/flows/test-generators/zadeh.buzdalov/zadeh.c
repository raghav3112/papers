/**
 * Generator of inputs for maximum flow according to Zadeh paper:
 *
 * Zadeh N. Theoretical Efficiency of the Edmonds-Karp Algorithm for Computing Maximal Flows
 * // Journal of the ACM. 1972. Vol. 19, no. 1, pp. 184-192.
 *
 * You can run it as follows:
 * - zadeh 1 N - to generate a test with N nodes which requires N^3 / 27 augmentations
 * - zaden 2 N - to generate a test with N nodes which requires N^3 / 12 augmentations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage() {
    fprintf(stderr, "Usage: zadeh <type> <nodes>\n");
    fprintf(stderr, "    where type is:\n");
    fprintf(stderr, "      1: for N^3/27 pattern from Zadeh\n");
    fprintf(stderr, "      2: for N^3/12 pattern from Zadeh\n");
    exit(1);
}

void edge(int src, int trg, int cap) {
    printf("a %d %d %d\n", src, trg, cap);
}

void gen27(int nodes) {
    int slot = nodes / 6;
    int first = 1, last = slot * 6;
    int lOffset = slot + 1;
    int rOffset = 5 * slot;
    int i, j;
    int edges = 12 * slot * slot + 2 * (slot - 1);

    nodes = last;

    printf("c Zadeh N^3/27 test generated by MaxBuzz\n");
    printf("p max %d %d\n", nodes, edges);
    printf("n %d s\n", first);
    printf("n %d t\n", last);

    int control = 0;
    for (i = 1; i <= slot; ++i) {
        int capacity = i == 1 ? 1 + 2 * slot : 2 + 4 * slot;
        for (j = 0; j < 2 * slot; ++j) {
            edge(first, i & 1 ? lOffset + j : rOffset - j, capacity);
            edge(i & 1 ? rOffset -j : lOffset + j, last, capacity);
            control += 2;
        }
    }
    for (i = 1; i < slot; ++i) {
        int capacity = nodes * slot - nodes * i + 1;
        edge(first + i - 1, first + i, capacity);
        edge(last - i, last - i + 1, capacity);
        control += 2;
    }
    for (i = 0; i < 2 * slot; ++i) {
        for (j = 0; j < 2 * slot; ++j) {
            edge(lOffset + i, rOffset - j, 1);
            edge(rOffset - j, lOffset + i, 1);
            control += 2;
        }
    }
    if (control != edges) {
        fprintf(stderr, "Failure: expected %d edges, generated %d", edges, control);
        exit(-1);
    }
}

void gen12(int nodes) {
}

int main(int argc, char *argv[]) {
    int type, nodes;
    if (argc != 3) {
        usage();
    }

    type = atoi(argv[1]);
    if (type < 1 || type > 2) {
        fprintf(stderr, "Error: illegal test type: '%s'", argv[1]);
        usage();
    }

    nodes = atoi(argv[2]);
    if (nodes <= 0) {
        fprintf(stderr, "Error: illegal number of nodes: '%s'", argv[2]);
        usage();
    }

    switch (type) {
        case 1: gen27(nodes); break;
        case 2: gen12(nodes); break;
    }

    return 0;
}
