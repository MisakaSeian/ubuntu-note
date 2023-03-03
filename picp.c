#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <strings.h>
#include <stdlib.h>
#include <linux/input.h>


#define IMG0 "AI.bmp"
#define IMG1 "A2.bmp"
#define IMG2 "A3.bmp"

//�л�BMPͼƬ��Ч��Բ��������
int pic_circular_shrink(char *pathname, int* pic_circular_shrink_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0, k=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_circular_shrink(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_circular_shrink(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_circular_shrink(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}

	//8�����⶯����Բ��������Ч���㷨
	for(k=468; k>=0; k-=3)
	{
		for(i=0; i<480; i++)
		{
			for(j=0; j<800; j++)
			{
				if((j-400)*(j-400)+(i-240)*(i-240) >= k*k)
					pic_circular_shrink_fd[800*i+j] = mi_buf[800*i+j];
			}
		}
	}	
		
	return 0;
}

//�л�BMPͼƬ��Ч��Բ����ɢ��
int pic_circular_spread(char *pathname, int* pic_circular_spread_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0, k=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname, O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_circular_spread(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_circular_spread(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_circular_spread(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}

	for(k=0; k<467; k+=3)//8�����⶯����Բ����ɢ��Ч���㷨
	{
		for(i=0; i<480; i++)
		{
			for(j=0; j<800; j++)
			{
				if((j-400)*(j-400)+(i-240)*(i-240) <= k*k)//(400,240)ΪԲ�ģ�kΪ�뾶��Բ
				{
					pic_circular_spread_fd[800*i+j] = mi_buf[800*i+j];					
				}
			}
		}
	} 

	return 0;
}

//�л�BMPͼƬ��Ч�����·��롰
int pic_down(char *pathname, int* pic_down_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0, k=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_down(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_down(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_down(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}

	//8�����⶯�������·��롱Ч���㷨
	for(i=0; i<480; i++)
	{
		for(j=0; j<800; j++)
		{
			pic_down_fd[800*i+j] = mi_buf[800*i+j];	
		}
		usleep(1000);
	} 	

	return 0;
}

//�л�BMPͼƬ��Ч�����Ϸ��롰
int pic_up(char *pathname, int* pic_up_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0, k=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_up(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_up(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_up(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}

	//8�����⶯�������Ϸ��롱Ч���㷨
	for(i=479; i>=0; i--)
	{
		for(j=0; j<800; j++)
		{
			pic_up_fd[800*i+j] = mi_buf[800*i+j];	
		}
		usleep(500);
	} 	
	
	return 0;
}

//�л�BMPͼƬ��Ч��������롰
int pic_left(char *pathname, int* pic_left_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0, k=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_left(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_left(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_left(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}

	//8�����⶯����������롱Ч���㷨
	for(j=799; j>=0; j--)
	{
		for(i=0; i<480; i++)
		{
			pic_left_fd[800*i+j] = mi_buf[800*i+j];
		}
		usleep(500);
	} 
	
	return 0;
}

//�л�BMPͼƬ��Ч�����ҷ��롰
int pic_right(char *pathname, int* pic_right_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0, k=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_right(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_right(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_right(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}

	//8�����⶯�������ҷ��롱Ч���㷨
	for(j=0; j<800; j++)
	{
		for(i=0; i<480; i++)
		{
			pic_right_fd[800*i+j] = mi_buf[800*i+j];
		}
		usleep(500);
	} 
		
	return 0;
}

//�л�BMPͼƬ��Ч�����Ҷ����
int pic_transverse_blinds(char *pathname, int* pic_transverse_blinds_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0, k=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_transverse_blinds(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_transverse_blinds(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_transverse_blinds(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}

	//8�����⶯�������Ҷ����Ч���㷨
	for(j=0; j<800/8; j++)
	{
		for(i=0; i<480; i++)
		{
			for(k=0; k<8; k++)
			{
				pic_transverse_blinds_fd[800*i+j+k*800/8] = mi_buf[800*i+j+k*800/8];
			}
		}
		usleep(500);
	}	 
		
	return 0;
}

//�л�BMPͼƬ��Ч������Ҷ����
int pic_vertical_blinds(char *pathname, int* pic_vertical_blinds_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0, k=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_vertical_blinds(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_vertical_blinds(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_vertical_blinds(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}

	//8�����⶯������Ҷ����Ч���㷨
	for(i=0; i<480/8; i++)
	{
		for(j=0; j<800; j++)
		{
			for(k=0; k<8; k++)
			{
				pic_vertical_blinds_fd[800*(i+k*480/8)+j] = mi_buf[800*(i+k*480/8)+j];
			}
		}
		usleep(500);
	}		
		
	return 0;
}
//�л�BMPͼƬ��Ч��������ϡ�
int pic_left_right_coincidence(char *pathname, int* pic_left_right_coincidence_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_left_right_coincidence(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_left_right_coincidence(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_left_right_coincidence(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}	

	for(block=0;block<10;block++)//8�����⶯����������ϡ�Ч���㷨
	{
		for(i=40*block;i<(block+1)*40;i++)//ˢ�󲿷־���
		{
			for(j=0;j<480;j++)
			pic_left_right_coincidence_fd[j*800+i]=mi_buf[j*800+i];
		}
		for(line=799-block*40;line>799-(block+1)*40;line--) //ˢ�Ҳ��־���
		{
			for(j=0;j<480;j++)
			pic_left_right_coincidence_fd[j*800+line]=mi_buf[j*800+line];
		}
		usleep(100000);	
	}

	return 0;
}

//�л�BMPͼƬ��Ч���м�չ����
int pic_mid_spread(char *pathname, int *pic_mid_spread_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_mid_spread(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_mid_spread(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_mid_spread(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}	

	//8�����⶯�����м�չ����Ч���㷨
	for(i=0; i<800/2; i++)
	{
		for(j=0; j<480; j++)
		{
			pic_mid_spread_fd[800/2+800*j+i] = mi_buf[800/2+800*j+i];
			pic_mid_spread_fd[800/2+800*j-i] = mi_buf[800/2+800*j-i];
		}
		usleep(500);
	}  

	return 0;
}

//�л�BMPͼƬ��Ч��б���顱
int pic_oblique_block(char *pathname, int *pic_oblique_block_fd)
{	
	int ret=0;
	int line=0;
	int block=0;
	int i=0, j=0, k=0;
	int m=0, n=0;
	int bmp_fd=0;
	
	char bmp_buf[480*800*3];
	int mi_buf[480*800];	
	int temp_buf[480*800];	
	bzero(mi_buf,sizeof(mi_buf));
	bzero(bmp_buf,sizeof(bmp_buf));
	bzero(temp_buf,sizeof(temp_buf));

	bmp_fd = open(pathname , O_RDONLY);//1����BMP��ʽͼƬ
	if(bmp_fd == -1)
	{
		printf("pic_oblique_block(), open bmp failed\n");
		return -1;
	}

	ret = lseek(bmp_fd, 54 , SEEK_SET);//2������bmpͼƬ��ǰ54��λ��
	if(ret == -1)
	{
		perror("pic_oblique_block(), lseek bmp failed\n");		
		return -1;
	}

	ret = read(bmp_fd , bmp_buf , sizeof(bmp_buf)); //4��ȡ��ͼƬ����
	if(ret == -1)
	{
		printf("pic_oblique_block(), read bmp failed\n");	
		return -1;
	}
	
	close(bmp_fd);//5���ر�ͼƬ

	for(i=0, j=0 ; i<800*480 ; i++, j+=3)//6��24bits ת 32bits���Ʊ���
	{
		temp_buf[i] = bmp_buf[j+2]<<16 | bmp_buf[j+1]<<8 | bmp_buf[j] ;
	}

	for(line=0 ; line <=480 ;line++)//7�����ͼƬ���µߵ�����
	{
		for(i=0; i<=800 ; i++)
		mi_buf[800*line + i] = temp_buf[ (479-line)*800 + i ];
	}	

	//8�����⶯����б���顱Ч���㷨
	for(k=0; k<=14; k++)
	{
		for(i=0; i<8; i++)
		{
			for(j=0; j<8; j++)
			{
				if(i+j <= k)
				{
					for(m=100*i; m<100*(i+1); m++)
					{
						for(n=60*j; n<60*(j+1); n++)
						{
							pic_oblique_block_fd[n*800+m] = mi_buf[n*800+m];
						}
					}
					usleep(200);
				}
			}
		}
	}

	return 0;
}
//lcd��ʼ��������ӳ��
int fd_init(int** fd_mmap)
{
	int lcd = open("/dev/fb0",O_RDWR);
	if(lcd == -1)
	{
		printf("lcd open fail!\n");
		return -1;
	}
	
	*fd_mmap = (int*)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd,0);
	
}



//����������л�
int pressure(char *pathname)
{
	struct input_event buf;
	int fd,x,y;
	fd = open("/dev/input/event0",O_RDWR);
	
	while(1)
	{
		read(fd,&buf,sizeof(buf));
		
		if(buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 1)
		{
			return 0;
		}

		if(buf.type == EV_ABS)
		{
			if(buf.code == ABS_X)
			{
				x = buf.value/1024.0*800;
			}
						
			return x;
		}
	}
}

int main()
{
	char* buf[]={IMG0,IMG1,IMG2};
	int *fd_mmap;
	int i=1000,index = 1;
	
	fd_init(&fd_mmap);
	
	while(1)
	{
				
		if(pressure(buf)>400)
		{			
			switch(index)
			{
				case 1:pic_circular_shrink(buf[i%3],fd_mmap); 			usleep(100);break;	
				case 2:pic_circular_spread(buf[i%3],fd_mmap); 			usleep(100);break;
				case 3:pic_down(buf[i%3],fd_mmap); 						usleep(100);break;
				case 4:pic_up(buf[i%3],fd_mmap); 						usleep(100);break;
				case 5:pic_left(buf[i%3],fd_mmap);						usleep(100);break;
				case 6:pic_right(buf[i%3],fd_mmap);						usleep(100);break;
				case 7:pic_transverse_blinds(buf[i%3],fd_mmap);			usleep(100);break;
				case 8:pic_vertical_blinds(buf[i%3],fd_mmap);  			usleep(100);break;
				case 9:pic_left_right_coincidence(buf[i%3],fd_mmap); 	usleep(100);break;
				case 10:pic_mid_spread(buf[i%3],fd_mmap);  				usleep(100);break;
				case 11:pic_oblique_block(buf[i%3],fd_mmap);index=0;	usleep(100);break;
			}
			index++;
			i++;
		}
		else{
			switch(index)
			{
				case 1:pic_circular_shrink(buf[i%3],fd_mmap); 			usleep(100);break;	
				case 2:pic_circular_spread(buf[i%3],fd_mmap); 			usleep(100);break;
				case 3:pic_down(buf[i%3],fd_mmap); 						usleep(100);break;
				case 4:pic_up(buf[i%3],fd_mmap); 						usleep(100);break;
				case 5:pic_left(buf[i%3],fd_mmap);						usleep(100);break;
				case 6:pic_right(buf[i%3],fd_mmap);						usleep(100);break;
				case 7:pic_transverse_blinds(buf[i%3],fd_mmap);			usleep(100);break;
				case 8:pic_vertical_blinds(buf[i%3],fd_mmap);  			usleep(100);break;
				case 9:pic_left_right_coincidence(buf[i%3],fd_mmap); 	usleep(100);break;
				case 10:pic_mid_spread(buf[i%3],fd_mmap);  				usleep(100);break;
				case 11:pic_oblique_block(buf[i%3],fd_mmap);index=0;	usleep(100);break;
			}
			index++;
			i--;
		}
	}
}