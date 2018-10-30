#include "ssl.h"

t_ullint	*copyHash512(t_ullint *hash)
{
	int			i;
	t_ullint	*tmp;

	i = 0;
	tmp = (t_ullint*)malloc(sizeof(t_ullint) * 8);
	while (i < 8)
	{
		tmp[i] = hash[i];
		i++;
	}
	return (tmp);
}

t_ullint	*generationWords512(t_ullint *w, t_ullint *arr)
{
	int			i;
	t_ullint	a;
	t_ullint	b;

	i = 0;
	w = (t_ullint*)malloc(sizeof(t_ullint) * 80);
	while (i < 16)
	{
		w[i] = arr[i];
		i++;
	}
	while (i < 80)
	{
		a = (fRotr512(w[i - 15], 1) \
				^ fRotr512(w[i - 15], 8) ^ (w[i - 15] >> 7));
		b = (fRotr512(w[i - 2], 19) ^ fRotr512(w[i - 2], 61) ^ (w[i - 2] >> 6));
		w[i] = w[i - 16] + a + w[i - 7] + b;
		i++;
	}
	return (w);
}

t_ullint	*hashSum512(t_ullint *hash, t_ullint *tmp)
{
	hash[A] = hash[A] + tmp[A];
	hash[B] = hash[B] + tmp[B];
	hash[C] = hash[C] + tmp[C];
	hash[D] = hash[D] + tmp[D];
	hash[E] = hash[E] + tmp[E];
	hash[F] = hash[F] + tmp[F];
	hash[G] = hash[G] + tmp[G];
	hash[H] = hash[H] + tmp[H];
	return (hash);
}

t_ullint	retElem2(int i)
{
	unsigned long long const int k[] = {
			0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
			0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
			0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
			0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
			0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
			0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
			0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
			0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
			0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
			0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
			0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
			0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
			0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
			0x5fcb6fab3ad6faec, 0x6c44198c4a475817
	};

	return (k[i - 39]);
}

t_ullint	retElem(int i)
{
	unsigned long long const int k[] = {
			0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
			0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
			0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
			0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
			0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
			0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
			0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
			0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
			0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
			0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
			0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
			0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
			0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	};

	if (i < 39)
		return (k[i]);
	else
		return (retElem2(i));
}

t_ullint	*formula512(t_ullint *fo, t_ullint *tmp, int i, t_ullint *words)
{
	fo[E0] = (fRotr512(tmp[A], 28) ^ fRotr512(tmp[A], 34) ^ fRotr512(tmp[A], 39));
	fo[MA] = (tmp[A] & tmp[B]) ^ (tmp[A] & tmp[C]) ^ (tmp[B] & tmp[C]);
	fo[T2] = fo[E0] + fo[MA];
	fo[E1] = (fRotr512(tmp[E], 14) ^ fRotr512(tmp[E], 18) ^ fRotr512(tmp[E], 41));
	fo[CH] = (tmp[E] & tmp[F]) ^ ((~tmp[E]) & tmp[G]);
	fo[T1] = tmp[H] + fo[E1] + fo[CH] + retElem(i) + words[i];
	return (fo);
}

t_ullint	*round512(t_ullint *tmp, t_ullint *words)
{
	int			i;
	t_ullint	*fo;

	fo = (t_ullint*)malloc(sizeof(t_ullint) * 6);
	i = 0;
	while (i < 80)
	{
		fo = formula512(fo, tmp, i, words);
		tmp[H] = tmp[G];
		tmp[G] = tmp[F];
		tmp[F] = tmp[E];
		tmp[E] = tmp[D] + fo[T1];
		tmp[D] = tmp[C];
		tmp[C] = tmp[B];
		tmp[B] = tmp[A];
		tmp[A] = fo[T1] + fo[T2];
		i++;
	}
	free(fo);
	return (tmp);
}

t_ullint	*alg512(t_ullint s, t_ullint *a, t_ullint *hash)
{
	t_ullint	j;
	t_ullint	*tmp;
	t_ullint	*words;
	int			g;

	g = 0;
	j = 0;
	while (j < s)
	{
		words = generationWords512(NULL, a + g);
		tmp = copyHash512(hash);
		tmp = round512(tmp, words);
		hash = hashSum512(hash, tmp);
		g += 16;
		j += 128;
		free(tmp);
		free(words);
	}
	free(a);
	return (hash);
}

t_ullint		findSize512(t_ullint len)
{
	t_ullint size;

	size = len * 8 + 1;
	while (size % 1024 != 896)
		size++;
	size = (size + 128) / 8;
	return (size);
}

t_uchar			*alignment512(t_ullint size, char *input)
{
	t_ullint	i;
	t_uchar		*res;

	res = (t_uchar*)malloc(sizeof(t_uchar) * (size));
	i = 0;
	while (i < size && input[i])
	{
		res[i] = (t_uchar)input[i];
		i++;
	}
	res[i++] = 0x80;
	while (i < size)
		res[i++] = 0;
	return (res);
}

t_ullint		*char2int512(t_uchar *bef, ssize_t news, t_ullint s)
{
	t_ullint	*aft;
	int			i;
	t_ullint	temp;
	int			b;

	i = 0;
	aft = (t_ullint*)malloc(sizeof(t_ullint) * news);
	while (i < news)
		aft[i++] = 0;
	s--;
	news--;
	while (news >= 0)
	{
		b = 0;
		while (b < 64)
		{
			temp = bef[s--];
			aft[news] = aft[news] | temp << b;
			b += 8;
		}
		news--;
	}
	free(bef);
	return (aft);
}

t_ullint		*writeLen512(t_ullint len, t_ullint *data, t_ullint i)
{
	data[i] = data[i] | len;
	return (data);
}

t_ullint	*initializeBuff512(t_ullint *hash)
{
	hash = (t_ullint*)malloc(sizeof(t_ullint) * 8);
	hash[0] = 0x6a09e667f3bcc908;
	hash[1] = 0xbb67ae8584caa73b;
	hash[2] = 0x3c6ef372fe94f82b;
	hash[3] = 0xa54ff53a5f1d36f1;
	hash[4] = 0x510e527fade682d1;
	hash[5] = 0x9b05688c2b3e6c1f;
	hash[6] = 0x1f83d9abfb41bd6b;
	hash[7] = 0x5be0cd19137e2179;
	return (hash);
}

void	printHash512(t_ullint *hash)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		ft_printf("%.16zx", hash[i]);
		i++;
	}
	free(hash);
}

void	SHA512(char *input, size_t len)
{
	t_ullint	size;
	t_uchar		*newinp;
	t_ullint	*res;
	t_ullint	*hash;

	size = findSize512(len);
	newinp = alignment512(size, input);
	res = initializeBuff512(NULL);
	hash = char2int512(newinp, (ssize_t)size / 8, size);
	hash = writeLen512(len * 8, hash, (size / 8) - 1);
	hash = alg512(size, hash, res);
	printHash512(hash);
}
