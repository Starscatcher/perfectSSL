#ifndef SSL_H
#define SSL_H

#include "./libftprintf/libft/libft.h"
typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;
typedef unsigned long long int	t_ullint;

#define	ALGO_NUM 3

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
void	findHashFunc(char *input,  t_flags *flags);

// bits operations
t_uint	fBit(t_uint x, t_uint y, t_uint z);
t_uint	gBit(t_uint x, t_uint y, t_uint z);
t_uint	hBit(t_uint x, t_uint y, t_uint z);
t_uint	lBit(t_uint x, t_uint y, t_uint z);
t_uint	f_rotr(t_uint a, int s);

// alignment for SHA256 & MD5
t_uchar	*ft_alignment(ssize_t size, char *input);
ssize_t	ft_find_size(ssize_t len);

// bonus from stdin
char	**fromStdin(int *argc, t_flags *flags);
char	**sslSplit(char *arr, char elem);

// algo
void	SHA256(char *input, t_flags *flags);
void	MD5(char *input, t_flags *flags);

#endif
