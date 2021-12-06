/*
 * main.c
 *
 * Created: 12/6/2021 2:35:16 PM
 *  Author: tolde
 */ 


static void setupApp(void)
{
	humidity_create();
	temperatura_create();
}
int main(void)
{
	setupApp();
	return 0;
}