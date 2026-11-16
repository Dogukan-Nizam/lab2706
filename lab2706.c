#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	srand(time(NULL));
	int Saglik, Enerji, Oksijen, Su, Yedek_Parca, Modul_Hasari, Tur_Sayisi, Gun_Sayisi, Zar, Esik, Hava_Kilidi, Hatali_Sifre, Miktar, Puan, Gecerli_Tur, Firtina_Suresi, Firtina_Son, Firtina_Hasari, Hasarli_Tur, Kaybedilen_Saglik, Kaybedilen_Oksijen;
	Gun_Sayisi = 1;
	Tur_Sayisi = 0;
	Gecerli_Tur = 0;
	Hava_Kilidi = 0;
	Hatali_Sifre = 0;
	Hasarli_Tur = 0;
	Kaybedilen_Saglik = 0;
	Kaybedilen_Oksijen = 0;
	char Zorluk, Komut, Sifre, Tahmin;
	float Zorluk_Carpani = 0;
	
	printf("[[[[---MARS KOLONISI YASAM DESTEK SIMULATORU---]]]]\nZorluk seviyesi seciniz. (K: Kolay, N: Normal, Z: Zor)\n");
do {
	scanf(" %c",&Zorluk);
	printf("\n");
	switch(Zorluk){
		case 'K':
		case 'k':
			Saglik = 75;
			Enerji = 75;
			Oksijen = 70;
			Su = 20;
			Yedek_Parca = 10;
			Modul_Hasari = 0;
			Zorluk_Carpani = 1;
			Firtina_Suresi = 3;
			break;
		case 'N':
		case 'n':
			Saglik = 60;
			Enerji = 60;
			Oksijen = 60;
			Su = 10;
			Yedek_Parca = 8;
			Modul_Hasari = 10;
			Zorluk_Carpani = 0.85;
			Firtina_Suresi = 4;
			break;
		case 'Z':
		case 'z':
			Saglik = 50;
			Enerji = 50;
			Oksijen = 40;
			Su = 5;
			Yedek_Parca = 5;
			Modul_Hasari = 25;
			Zorluk_Carpani = 0.7;
			Firtina_Suresi = 5;
		break;
		default:
			printf("Gecersiz girdi.\n");
			break;
		}
} while(Zorluk_Carpani == 0);
	do {		
				printf("\nYapilacak islemi seciniz.\nG: Kesif Gorevi\nO: Oksijen Uret\nT: Tamir\nD: Durum Raporu\nU: Uyu\nK: Kum Firtinasi\nH: Hava kilidini muhurle\nQ: Oyunu sonlandir\n\n");
				scanf(" %c",&Komut);
				switch(Komut){
					case 'G':
					case 'g':
						if ((Enerji <= 15) && (Oksijen > 10)) {
							printf("Yetersiz enerji.\n");
							break;
						} else if ((Enerji > 15) && (Oksijen <= 10)) {
							printf("Yetersiz oksijen.\n");
							break;
						} else if ((Enerji <= 15) && (Oksijen <= 10)) {
							printf("Yetersiz enerji ve oksijen.\n");
							break;
						} else {
						Esik = 80 * Zorluk_Carpani;
						if (Enerji > 40 && Oksijen > 30){
							Esik = Esik + 10;
						}
						Enerji = Enerji - 15;
						Oksijen = Oksijen - 10;
						Zar = rand() % 100;
						if(Zar < 10 || Modul_Hasari > 70) {
							printf("Kesif sirasinda yaralandin. Sagligin 10 azaldi.\n");
							Saglik = Saglik - 10;
						}
						if(Zar > Esik){
							printf("Zar: %d / Esik: %d -> BASARISIZ\nHicbir sey bulamadin.\n",Zar,Esik);
							Gecerli_Tur = 1;
							break;
						}
						if(Zar <= Esik && Zar > (40 * Zorluk_Carpani)) {
							printf("Zar: %d / Esik: %d -> BASARILI\n%d Litre su buldun.\n",Zar,Esik, 500 / Zar);
							Su = Su + 500 / Zar;
							Gecerli_Tur = 1;
							break;
						}
						if(Zar <= (40 * Zorluk_Carpani) && Zar > (20 * Zorluk_Carpani)) {
							printf("Zar: %d / Esik: %d -> BASARILI\n%d Yedek parca buldun.\n",Zar,Esik, 150 / Zar);
							Yedek_Parca = Yedek_Parca + 150 / Zar;
							Gecerli_Tur = 1;
							break;
						}
						if(Zar <= (20 * Zorluk_Carpani)) {
							printf("Zar: %d / Esik: %d -> BASARILI\n%d Litre su ve %d yedek parca buldun.\n",Zar,Esik, 400 / (Zar + 19), 200 / (Zar + 19));
							Su = Su + 400 / (Zar + 19);
							Yedek_Parca = Yedek_Parca + 200 / (Zar + 19);
							Gecerli_Tur = 1;
							break;
						}
					}
					case 'O':
					case 'o':
						if(Enerji >=5){
						if(Su >= 2){
							if((100 - Oksijen) >= 3){
								printf("Kac litre su kullanmak istediginizi giriniz. (2X Litre su + 5 enerji = 3X Litre oksijen.)\n");
								scanf("%d",&Miktar);
								if(Miktar <= 0){
									printf("Gecersiz deger.\n");
									break;
								}
								if(Miktar <= Su){
									if((Miktar / 2) * 3 + Oksijen <= 100){
										if(Miktar % 2 == 0){
										printf("Islem sonucunda %d Litre su kullanilarak %d Litre oksijen uretilmistir.\n", Miktar, (Miktar / 2) * 3);
										Su = Su - Miktar;
										Oksijen = Oksijen + (Miktar / 2) * 3;
										Enerji = Enerji - 5;
										Gecerli_Tur = 1;
										break;
										} else {
											Miktar = Miktar - 1;
											printf("Islem sonucunda %d Litre su kullanilarak %d Litre oksijen uretilmistir.\n", Miktar, (Miktar / 2) * 3);
											Su = Su - Miktar;
											Oksijen = Oksijen + (Miktar / 2) * 3;
											Enerji = Enerji - 5;
											Gecerli_Tur = 1;
											break;
										}
									} else {
										printf("Oksijen deposunda %d Litre su kullanilmasiyla ortaya cikacak oksijen icin yeterli yer yoktur.\n",Miktar);
										Miktar = (100 - Oksijen) / 3;
										printf("Kullanabileceginiz maksimum su miktari %d Litredir.\n", Miktar * 2);
										break;
									}
								} else {
									printf("Depoda bu miktar su bulunmamaktadir.\n");
									break;
								}
							} else {
								printf("Oksijen deposunda yer bulunmamaktadir.\n");
								break;
							}
						} else {
							printf("Yeterli miktar su bulunmamaktadir.\n");
							break;
						}
						} else {
							printf("Yeterli miktar enerji bulunmamaktadir.\n");
							break;
						}
					case 'T':
					case 't':
						printf("Modul hasari: %d\n", Modul_Hasari);
						if (Modul_Hasari == 0){
							printf("Tamire gerek yok.\n");
							break;
						} else if (Yedek_Parca == 0){
							printf("Yedek parca yok.\n");
							break;
						} else if (Modul_Hasari < 36){
							printf("Dusuk seviye modul hasari.\nTamir icin 10 yedek parca gerekli.\n");
							if (Yedek_Parca >= 10){
								printf("Tamir edildi.\n");
								Modul_Hasari = Modul_Hasari - 25;
								Yedek_Parca = Yedek_Parca - 10;
								Gecerli_Tur = 1;
								break;
							} else {
								printf("Yeterli sayida yedek parca yok.\n");
								break;
							}
						} else if (Modul_Hasari < 70){
							printf("Orta seviye modul hasari.\nTamir icin 15 yedek parca gerekli.\n");
							if(Yedek_Parca >= 15){
								printf("Tamir edildi.\n");
								Modul_Hasari = Modul_Hasari - 40;
								Yedek_Parca = Yedek_Parca - 15;
								Gecerli_Tur = 1;
								break;
							} else {
								printf("Yeterli sayida yedek parca yok.\n");
								break;
								}
						} else {
								printf("Kritik seviye modul hasari.\nTamir icin 20 yedek parca gerekli.\n");
								if (Yedek_Parca >= 20){
									printf("Tamir edildi.\n");
									Modul_Hasari = Modul_Hasari - 60;
									Yedek_Parca = Yedek_Parca - 20;
									Gecerli_Tur = 1;
									break;
								} else {
									printf("Yeterli sayida yedek parca yok.\n");
									break;
								}
						}
					case 'D':
					case 'd':
						if ((Saglik > 10) && (Oksijen > 20) && (Modul_Hasari < 70)) {
							printf("TUM SISTEMLER NORMAL\n");
						} else {
							if(Saglik <= 10) {
							printf("SAGLIK SEVIYESI KRITIK\n");
							}
							if(Oksijen <= 20) {
							printf("OKSIJEN SEVIYESI KRITIK\n");
							}
							if(Modul_Hasari >= 70) {
							printf("MODUL HASARI KRITIK\n");
							}
						}
						printf("Gun: %d\nTur: %d\nEnerji: %d/100\nSaglik: %d/100\nOksijen: %d/100\nSu: %d Litre\nYedek parca sayisi: %d\nModul hasari: %d/100\n",Gun_Sayisi,Tur_Sayisi,Enerji,Saglik,Oksijen,Su,Yedek_Parca,Modul_Hasari);
						break;
					case 'U':
					case 'u':
						if ((Enerji < 50) || (Saglik < 60)){
							if (Oksijen > 20){
								printf("Uyudun. Enerjin ve Sagligin artti.\n");
								Enerji = Enerji + 50;
								Saglik = Saglik + 30;
								Gecerli_Tur = 1;
								break;
							}
							if (Oksijen <= 20){
								printf("Uyudun. Enerjin arttý.\nKritik oksijen seviyesi. Sagligin azaldi.\n");
								Enerji = Enerji + 50;
								Saglik = Saglik - 10;
								Gecerli_Tur = 1;
								break;
							}
						} else {
							printf("Uykuya ihtiyac yok.\n");
							break;
						}
					case 'K':
					case 'k':
						printf("Kum firtinasi baslatildi. %d Tur sürecek.\n",Firtina_Suresi);
						for (Firtina_Son = Tur_Sayisi + Firtina_Suresi; Tur_Sayisi < Firtina_Son; Tur_Sayisi++){
							if ((Tur_Sayisi % 2) == 0){
								Firtina_Hasari = 30;
							} else {
								Firtina_Hasari = 15;
							}
							Zar = rand() % 100;
							if(Modul_Hasari > 70){
								Esik = 40;
							} else {
								Esik = 50;
							}
							if (Zar < Esik){
								printf("Firtinadan zarar gormedin.\n");
							} else if (Zar < 60) {
								if (Hava_Kilidi == 1){
									printf("Oksijen sizintisi. Hava kilidi muhurlu, firtinadan zarar gormedin.\n");
									continue;
								} else {
									printf("Oksijen sizintisi. %d Oksijen kaybettin.\n", Firtina_Hasari);
									Oksijen = Oksijen - Firtina_Hasari;
									Hasarli_Tur = Hasarli_Tur + 1;
									Kaybedilen_Oksijen = Kaybedilen_Oksijen + Firtina_Hasari;
								}	
							} else if (Zar < 80) {
								printf("Sarsinti. %d Saglik kaybettin.\n", Firtina_Hasari);
								Saglik = Saglik - Firtina_Hasari;
								Hasarli_Tur = Hasarli_Tur + 1;
								Kaybedilen_Saglik = Kaybedilen_Saglik + Firtina_Hasari;
							} else {
								printf("Savrulan cisimler. %d Modul hasari aldin.\n", Firtina_Hasari);
								Modul_Hasari = Modul_Hasari + Firtina_Hasari;
								Hasarli_Tur = Hasarli_Tur + 1;
							}
							if (Saglik < 0){
								Saglik = 0;
							}
							if (Oksijen < 0){
								Oksijen = 0;
							}
							if (Enerji < 0){
								Enerji = 0;
							}
							if (Modul_Hasari < 0){
								Modul_Hasari = 0;
							}
							if (Saglik > 100){
								Saglik = 100;
							}
							if (Oksijen > 100){
								Oksijen = 100;
							}
							if (Enerji > 100){
								Enerji = 100;
							}
							if (Modul_Hasari > 100){
								Modul_Hasari = 100;
							}
							if ((Saglik == 0) || (Oksijen == 0)){
								break;
							}
						}
						printf("Firtina ozeti:\nHasar alinan tur sayisi: %d\nKaybedilen toplam saglik: %d\nKaybedilen toplam oksijen: %d\n", Hasarli_Tur, Kaybedilen_Saglik, Kaybedilen_Oksijen);
						break;
					case 'H':
					case 'h':
						Hatali_Sifre = 0;
						if (Hava_Kilidi == 1){
							printf("Hava kilidi zaten muhurlu.\n");
							break;
						}
						Sifre = 'O' - Gun_Sayisi;
						printf("Sifre alfabede 15. harften baslayip gun gectikce geri gider.\n");
						do {
							scanf(" %c",&Tahmin);
							if((Tahmin >= 'a') && (Tahmin <= 'z')){
								Tahmin = Tahmin - 32;
							}
							if(Sifre != Tahmin){
								Hatali_Sifre = Hatali_Sifre + 1;
								printf("Sifre yanlis girildi. Enerji 5 azaldi. Kalan deneme hakki: %d\n", 3 - Hatali_Sifre);
								Enerji = Enerji - 5;
								if(Tahmin > Sifre){
									printf("Geri git.\n");
								} else {
									printf("Ileri git.\n");
								}
							}
						} while((Sifre != Tahmin) && Hatali_Sifre != 3);
						if(Sifre == Tahmin){
							printf("Sifre dogru girildi. Hava kilidi muhurlendi.\n");
							Hava_Kilidi = 1;
							Gecerli_Tur = 1;
							break;
						} else {
							printf("Sifre bilinemeden deneme hakki bitti. Modul hasari 20 arttý.\n");
							Modul_Hasari = Modul_Hasari + 20;
							Gecerli_Tur = 1;
							break;
						}
					case 'Q':
					case 'q':
						printf("\nOyunu sonlandirdin.\n");
						continue;
					default:
						printf("Gecersiz girdi.\n");
						break;
				}
			if(Gecerli_Tur == 1){
				Gecerli_Tur = 0;
				Tur_Sayisi = Tur_Sayisi + 1;
				if((Tur_Sayisi % 3) == 0){
					Gun_Sayisi = Gun_Sayisi + 1;
					Oksijen = Oksijen - 8;
					printf("\n-------%d. Gun-------\n",Gun_Sayisi);
					if(Modul_Hasari > 70){
						Saglik = Saglik - 5;
						printf("Kritik modul hasari. 5 Saglik kaybettin.");
					}
				}
			}
			if (Saglik < 0){
					Saglik = 0;
				}
				if (Oksijen < 0){
					Oksijen = 0;
				}
				if (Enerji < 0){
					Enerji = 0;
				}
				if (Modul_Hasari < 0){
					Modul_Hasari = 0;
				}
				if (Saglik > 100){
					Saglik = 100;
				}
				if (Oksijen > 100){
					Oksijen = 100;
				}
				if (Enerji > 100){
					Enerji = 100;
				}
				if (Modul_Hasari > 100){
					Modul_Hasari = 100;
				}
			} while ((Saglik > 0 && Oksijen > 0) && (Gun_Sayisi <= 16) && ((Komut != 'q') && (Komut != 'Q')));
			if (Saglik == 0){
				printf("\nSagligin 0'a dustu. Oyunu Kaybettin.\n");
			} else if (Oksijen == 0){
				printf("\nOksijen 0'a dustu. Oyunu Kaybettin.\n");
			} else if (Gun_Sayisi == 16){
				printf("\n15. gun sona erdi ve yardim geldi. Oyunu Kazandin.\n");
			}
	printf("Oyun sonu istatistikleri:\n%d Gun hayatta kalindi\n%d Tur oynandi\n\nSon durum degerleri:\nEnerji: %d/100\nSaglik: %d/100\nOksijen: %d/100\nSu: %d Litre\nYedek parca sayisi: %d\nModul hasari: %d/100\n",Gun_Sayisi - 1, Tur_Sayisi,Enerji,Saglik,Oksijen,Su,Yedek_Parca,Modul_Hasari);
	if (Hava_Kilidi == 1){
	printf("Hava kilidi: Muhurlendi\n");
	} else {
	printf("Hava kilidi: Muhurlenmedi\n");
	}
	Puan = (((Gun_Sayisi - 1) * 500) + (Saglik * 5) + (Oksijen * 5) + (Enerji * 5) + (Hava_Kilidi * 1000) - (Modul_Hasari * 10)) * (1 / Zorluk_Carpani);
	printf("Alinan puan: %d",Puan);
	return 0;
}

