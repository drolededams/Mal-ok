#include "inc/malloc.h"
#include <string.h>

void *malloc_array(void *adr)
{
	adr = malloc(16);
	return (adr);
}

void *free_array(void *adr)
{
	free(adr);
	return (NULL);
}

void *real_array(void *adr)
{
	adr = realloc(adr, 32);
	return (NULL);
}

void *real_array2(void *adr)
{
	adr = realloc(adr, 32);
	free(adr);
	return (NULL);
}

int main() 
{ 

	char *adr0; 
	char *adr1; 
	char *adr2; 
	char *adr3; 
	char *adr4; 
	char *adr5; 
	char *adr6; 


	ft_putendl("================Calloc====================");
	ft_putendl("");

	ft_putendl("==init==");
	ft_putendl("");
	adr0 = (char*)malloc(16); 
	adr0[0] = 42; 
	adr0[1] = 43; 
	adr1 = (char*)malloc(16); 
	adr1[0] = 44; 
	adr1[1] = 45; 
	//show_alloc_mem_hex();
	show_alloc_mem_ex();
	//show_alloc_mem();

	ft_putendl("==result==");
	ft_putendl("");
	free(adr1);
	adr1 = calloc(2, 8); 
	//show_alloc_mem_hex();
	show_alloc_mem_ex();
	//show_alloc_mem();


	ft_putendl("");
	ft_putendl("================Free Defrag====================");
	ft_putendl("");

	ft_putendl("==init==");
	ft_putendl("");
	adr2 = (char*)calloc(2, 8);
	adr2[0] = 44; 
	adr3 = (char*)calloc(2, 8);
	adr3[0] = 45; 
	adr4 = (char*)calloc(2, 8);
	adr4[0] = 46; 
	show_alloc_mem();
	//show_alloc_mem_ex();
	free(adr2);
	free(adr3);

	ft_putendl("");
	ft_putendl("==result==");
	ft_putendl("");
	adr5 = (char*)malloc(64);
	adr5[0] = 47; 
	adr5[16] = 48; 
	show_alloc_mem();
	
	
	
	
	ft_putendl("");
	ft_putendl("================Reallocarray====================");
	ft_putendl("");
	ft_putendl(strerror(errno));
	adr6 = reallocarray(adr5, 4294967296, 4294967297);
	ft_putendl(strerror(errno));
	show_alloc_mem();
	//show_alloc_mem_ex();
	ft_putendl("free all");
	free(adr0);
	free(adr1);
	free(adr4);
	free(adr5);
	free(adr6);
	show_alloc_mem();
	show_alloc_mem();
	show_alloc_mem_hex();
	show_alloc_mem();
	//show_alloc_mem_ex();
	
	ft_putendl("");
	ft_putendl("================THREAD====================");
	ft_putendl("");
	
	ft_putendl("=Malloc=");
	ft_putendl("");
	pthread_t mal[3];
	pthread_t free[4];
	pthread_t real[2];
	pthread_create(&mal[0], NULL, malloc_array, adr0);
	pthread_create(&mal[1], NULL, malloc_array, adr1);
	pthread_create(&mal[2], NULL, malloc_array, adr5);
	pthread_join(mal[0], NULL);
	pthread_join(mal[1], NULL);
	pthread_join(mal[2], NULL);
	show_alloc_mem();
	//show_alloc_mem_ex();
	
	ft_putendl("");
	ft_putendl("=Free=");
	ft_putendl("");
	pthread_create(&free[0], NULL, free_array, adr0);
	pthread_create(&free[1], NULL, free_array, adr0);
	pthread_create(&free[2], NULL, free_array, adr1);
	pthread_create(&free[3], NULL, free_array, adr5);
	pthread_join(free[0], NULL);
	pthread_join(free[1], NULL);
	pthread_join(free[2], NULL);
	pthread_join(free[3], NULL);
	show_alloc_mem();
	//show_alloc_mem_ex();
	
	ft_putendl("");
	ft_putendl("=Realloc=");
	ft_putendl("");
	adr0 = (char*)malloc(16);
	adr5 = (char*)malloc(16);
	ft_putendl("");
	ft_putendl("==init==");
	ft_putendl("");
	show_alloc_mem();
	//show_alloc_mem_ex();
	pthread_create(&real[1], NULL, real_array, adr5);
	pthread_create(&real[0], NULL, real_array, adr0);
	pthread_join(real[1], NULL);
	pthread_join(real[0], NULL);
	ft_putendl("");
	ft_putendl("==result==");
	ft_putendl("");
	show_alloc_mem();
	return (0); 
} 
