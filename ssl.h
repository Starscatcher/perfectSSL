#ifndef SSL_H
#define SSL_H

#include "./libftprintf/libft/libft.h"
typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;
typedef unsigned long long int	t_ullint;

#define	ALGO_NUM 6

# define BUFF_SIZE 1

# define A 0
# define B 1
# define C 2
# define D 3
# define E 4
# define F 5
# define G 6
# define H 7
# define E0 0
# define MA 1
# define T2 2
# define E1 3
# define CH 4
# define T1 5

typedef struct	s_flags
{
	int p;
	int q;
	int r;
	int s;

	int d;

	char *algName;
	int algInd;
	int file;
	int stdin;
}				t_flags;

typedef	struct	s_algo
{
	char			*name;
	struct	s_algo	*next;
}				t_algo;

typedef struct	s_md
{
  unsigned int	a;
  unsigned int	aa;
  struct s_md		*next;
}				t_md;

typedef void	(*t_alg)(char *, t_flags *);

// create/delete struct
t_algo	*createAlgoStruct(char *allAlgs);
void	delAlgoStruct(t_algo *algo);
t_flags	*createFlagsStruct(void);
void	delFlagsStruct(t_flags *flags);
t_md	*createMdStruct(t_md *lst);
void	delMdStruct(t_md *md);

// read args
void	readArgs(t_flags *flags, t_algo *algo, int argc, char **argv);
int		findAlgo(t_algo *algo, t_flags *flags, char *arg);

// errors
void	algoError(t_algo *algo, char *arg);
void	optionError(char *arg);
void	fileError(char *arg, t_flags *flags);
void	usage();

// read FD
char	*readFd(int fd);

// searching right algorithm
void	findFunc(char *input,  t_flags *flags);

// bits operations
t_uint		fBit(t_uint x, t_uint y, t_uint z);
t_uint		gBit(t_uint x, t_uint y, t_uint z);
t_uint		hBit(t_uint x, t_uint y, t_uint z);
t_uint		lBit(t_uint x, t_uint y, t_uint z);
t_uint		fRotr(t_uint a, int s);
t_ullint	fRotr512(t_ullint a, int s);

// alignment for SHA256 & MD5
t_uchar	*ft_alignment(ssize_t size, char *input);
ssize_t	ft_find_size(ssize_t len);

// bonus from stdin
char	**fromStdin(int *argc, t_flags *flags);
char	**sslSplit(char *arr, char elem);

// SHA512 384
t_uchar			*alignment512(t_ullint size, char *input);
t_ullint		findSize512(t_ullint len);
t_ullint		*char2int512(t_uchar *bef, ssize_t news, t_ullint s);
t_ullint		*writeLen512(t_ullint len, t_ullint *data, t_ullint i);
t_ullint		*alg512(t_ullint s, t_ullint *a, t_ullint *hash);

// SHA 256 224
t_uint	*char2int256(t_uchar *bef, ssize_t newsize, ssize_t size);
t_uint	*writeLen256(ssize_t len, t_uint *data, ssize_t i);
t_uint	*algSHA256(ssize_t size, t_uint *arr, t_uint *hash);

// algo
void	SHA256(char *input, t_flags *flags);
void	MD5(char *input, t_flags *flags);
void	SHA512(char *input, t_flags *flags);
void	SHA384(char *input, t_flags *flags);
void	SHA224(char *input, t_flags *flags);

void	BASE64(char *input, t_flags *flags);

#endif
