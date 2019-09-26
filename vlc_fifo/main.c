#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <unistd.h>


#include "vlc_block.h"

void *producer_thread(void *pram)
{
	block_fifo_t *pFifo = (block_fifo_t*)pram;

	printf("wang producer start----------- [%d%s]\n",__LINE__,__FUNCTION__);
	char testBuf[][30]={"aaa","bbb","ccc","ddd","eee","fff"};
	int i =0; 

	for(i=0; i<sizeof(testBuf)/sizeof(testBuf[0]); i++)
	{
		block_t * temp = block_Alloc(40);
		if(temp)
		{
			memcpy(temp->p_buffer,testBuf[i],sizeof(testBuf[i]));
			block_FifoPut(pFifo, temp);
		}

		usleep(1000*500);
	}
	printf("wang producer over--------------- [%d%s]\n",__LINE__,__FUNCTION__);
}
int main()
{

	printf("Tips !! chekc your system 32bit or 64bit, Now the demo defind %s-bit\n",sizeof(uintptr_t) == 8?"64":"32");
	block_fifo_t *pFifo = block_FifoNew();
	if(!pFifo)
	{
		printf("create fifo erro\n");
		return -1;
	}
	pthread_t producer;
	if(pthread_create(&producer,NULL,producer_thread,(void*)pFifo))
	{
		printf("create thread erro [%d%s]\n",__LINE__,__FUNCTION__);
		return -1;
	}
	else
	{
		 pthread_detach(producer);
	}

	//printf("count %ld, byte %ld [%d%s]\n",block_FifoCount(pFifo),block_FifoSize(pFifo),__LINE__,__FUNCTION__);	
	while(1)
	{	
		block_t * temp = block_FifoGet(pFifo);
		printf("get one: %s\n",temp->p_buffer);
		block_Release(temp);
		//printf("count %ld, byte %ld [%d%s]\n",block_FifoCount(pFifo),block_FifoSize(pFifo),__LINE__,__FUNCTION__);
	}

	block_FifoRelease(pFifo);
}
