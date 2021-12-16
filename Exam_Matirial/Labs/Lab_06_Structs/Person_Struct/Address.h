#ifndef ADDRESS_H_
#define ADDRESS_H_


#define LEN 20

typedef struct
{
	int		num;
	char	street[LEN];
} Address;

void	initAddress(Address* pAd);
void	printAddress(const Address* pAd);

#endif /* ADDRESS_H_ */
