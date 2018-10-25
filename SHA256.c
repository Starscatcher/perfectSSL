#include "ssl.h"

t_uint		*ft_copy_hash(t_uint *hash)
{
	int		i;
	t_uint	*tmp;

	i = 0;
	tmp = (unsigned int*)malloc(sizeof(unsigned int) * 8);
	while (i < 8)
	{
		tmp[i] = hash[i];
		i++;
	}
	return (tmp);
}

t_uint	*ft_generation_words(t_uint *w, t_uint *arr)
{
	int		i;
	t_uint	a;
	t_uint	b;

	i = 0;
	w = (t_uint*)malloc(sizeof(t_uint) * 64);
	while (i < 16)
	{
		w[i] = arr[i];
		i++;
	}
	while (i < 64)
	{
		a = (f_rotr(w[i - 15], 7) ^ f_rotr(w[i - 15], 18) ^ (w[i - 15] >> 3));
		b = (f_rotr(w[i - 2], 17) ^ f_rotr(w[i - 2], 19) ^ (w[i - 2] >> 10));
		w[i] = w[i - 16] + a + w[i - 7] + b;
		i++;
	}
	return (w);
}

t_uint	*ft_hash_plus_newhash(t_uint *hash, t_uint *tmp)
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

t_uint	*ft_formula(t_uint *fo, t_uint *tmp, int i, t_uint *words)
{
	unsigned const int k[] = {
			0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B,
			0x59F111F1, 0x923F82A4, 0xAB1C5ED5, 0xD807AA98, 0x12835B01,
			0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7,
			0xC19BF174, 0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
			0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA, 0x983E5152,
			0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147,
			0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138, 0x4D2C6DFC,
			0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
			0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819,
			0xD6990624, 0xF40E3585, 0x106AA070, 0x19A4C116, 0x1E376C08,
			0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F,
			0x682E6FF3, 0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
			0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
	};

	fo[E0] = (f_rotr(tmp[A], 2) ^ f_rotr(tmp[A], 13) ^ f_rotr(tmp[A], 22));
	fo[MA] = (tmp[A] & tmp[B]) ^ (tmp[A] & tmp[C]) ^ (tmp[B] & tmp[C]);
	fo[T2] = fo[E0] + fo[MA];
	fo[E1] = (f_rotr(tmp[E], 6) ^ f_rotr(tmp[E], 11) ^ f_rotr(tmp[E], 25));
	fo[CH] = (tmp[E] & tmp[F]) ^ ((~tmp[E]) & tmp[G]);
	fo[T1] = tmp[H] + fo[E1] + fo[CH] + k[i] + words[i];
	return (fo);
}

t_uint	*ft_round(t_uint *tmp, t_uint *words)
{
	int		i;
	t_uint	*fo;

	fo = (t_uint*)malloc(sizeof(t_uint) * 6);
	i = 0;
	while (i < 64)
	{
		fo = ft_formula(fo, tmp, i, words);
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

t_uint	*ft_alg_sha256(ssize_t size, t_uint *arr, t_uint *hash)
{
	int		j;
	t_uint	*tmp;
	t_uint	*words;
	int		g;

	g = 0;
	j = 0;
	while (j < size)
	{
		words = ft_generation_words(NULL, arr + g);
		tmp = ft_copy_hash(hash);
		tmp = ft_round(tmp, words);
		hash = ft_hash_plus_newhash(hash, tmp);
		g += 16;
		j += 64;
		free(tmp);
		free(words);
	}
	free(arr);
	return (hash);
}

t_uint		*ft_initialize_buff_sha256(t_uint *hash)
{
	hash = (t_uint*)malloc(sizeof(t_uint) * 8);
	hash[0] = 0x6A09E667;
	hash[1] = 0xBB67AE85;
	hash[2] = 0x3C6EF372;
	hash[3] = 0xA54FF53A;
	hash[4] = 0x510E527F;
	hash[5] = 0x9B05688C;
	hash[6] = 0x1F83D9AB;
	hash[7] = 0x5BE0CD19;
	return (hash);
}

t_uint	*ft_char2int_sha256(t_uchar *bef, ssize_t newsize, ssize_t size)
{
	t_uint	*aft;
	int		i;

	i = 0;
	aft = (t_uint*)malloc(sizeof(t_uint) * newsize);
	while (i < newsize)
		aft[i++] = 0;
	size--;
	newsize--;
	while (newsize >= 0)
	{
		aft[newsize] = aft[newsize] | bef[size--] << 0;
		aft[newsize] = aft[newsize] | bef[size--] << 8;
		aft[newsize] = aft[newsize] | bef[size--] << 16;
		aft[newsize] = aft[newsize] | bef[size--] << 24;
		newsize--;
	}
	free(bef);
	return (aft);
}

t_uint	*ft_write_len_sha256(ssize_t len, t_uint *data, ssize_t i)
{
	while (len)
	{
		data[i] = data[i] | (t_uint)len << 0;
		len = len >> 8;
		data[i] = data[i] | (t_uint)len << 8;
		len = len >> 8;
		data[i] = data[i] | (t_uint)len << 16;
		len = len >> 8;
		data[i] = data[i] | (t_uint)len << 24;
		len = len >> 8;
		i--;
	}
	return (data);
}

t_uint	*hashSHA256(char *input, size_t len)
{
	ssize_t	size;
	t_uchar	*newinp;
	t_uint	*arr;
	t_uint	*hash;

	size = ft_find_size(len);
	newinp = ft_alignment(size, input);
	hash = ft_initialize_buff_sha256(NULL);
	arr = ft_char2int_sha256(newinp, size / 4, size);
	arr = ft_write_len_sha256((len * 8), arr, ((size / 4) - 1));
	return (ft_alg_sha256(size, arr, hash));
}

void	printHash256(t_uint *hash)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		ft_printf("%.8x", hash[i]);
		i++;
	}
}

void	SHA256(char *input, t_flags *flags)
{
	size_t len;

	len = ft_strlen(input);
	if ((flags->p || flags->s) && !flags->q && !flags->file && !flags->r)
		ft_printf("%s ( %s ) = ", flags->algName, input);
	printHash256(hashSHA256(input, len));
	if (flags->r && !flags->q && !flags->file)
		ft_printf(" \"%s\"\n", input);
	else if (flags->file)
		ft_printf(" %s\n", input);
	else
		ft_printf("\n");
}
