#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include"lru_cache.h"

/*
 * TODO LRU delete
 * TODO remove old entries
 *
 */


int main(){

        FILE *file_ptr[4];
        char files_to_open[4][16]       =       {"a.txt", "b.txt", "c.txt", "d.txt"};

        for(int i = 0; i < 4;i++ ){
                file_ptr[i] = lru_open_file( files_to_open[i] );
        }

        for(int i = 0; i < 4;i++ ){
                if ( lru_search( files_to_open[i] )){
                        printf("%s entry is available in lru\n", files_to_open[i]);
                }else{
                        printf("%s entry not available in lru\n", files_to_open[i]);
                }
        }

        print_lru_stats();

        for(int i = 0; i < 4;i++ ){
                lru_close_file( file_ptr[i] , files_to_open[i]);
        }
        return 0;
}