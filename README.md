# Mars Kolonisi Yaşam Destek Simülatörü

C dilinde yazılmış, konsol tabanlı bir hayatta kalma simülasyonudur. Oyuncu, Mars’taki küçük bir araştırma 
istasyonunda tek başına kalmış bir mühendisi yönetir ve kurtarma ekibi gelene kadar 15 gün 
hayatta kalmaya çalışır.

## İçindekiler

- [Özellikler](#özellikler)
- [Derleme ve çalıştırma](#derleme-ve-çalıştırma)
- [Oyunun amacı](#oyunun-amacı)
- [Zorluk seviyeleri](#zorluk-seviyeleri)
- [Komutlar](#komutlar)
- [Kum fırtınası](#kum-fırtınası)
- [Hava kilidi şifresi](#hava-kilidi-şifresi)
- [Tur ve gün sistemi](#tur-ve-gün-sistemi)
- [Değer sınırları](#değer-sınırları)
- [Oyun sonu ve puanlama](#oyun-sonu-ve-puanlama)
- [Kullanılan C yapıları](#kullanılan-c-yapıları)

## Özellikler

- Üç zorluk seviyesi (Kolay, Normal, Zor)
- Menü tabanlı, sekiz komutlu oyun akışı
- Zar atışına dayalı rastgele olaylar (keşif ve kum fırtınası)
- Çift/tek tura göre değişen fırtına hasarı
- Şifre tahmin mekanizmasıyla hava kilidi mühürleme
- Oyun sonunda istatistik ve puan hesaplama

## Derleme ve çalıştırma

Program yalnızca standart C kütüphanelerini kullanır (`stdio.h`, `stdlib.h`, `time.h`). Ek bir bağımlılık gerekmez.

**Dev-C++ ile:** Kaynak dosyayı açın, `F11` tuşuyla derleyip çalıştırın.

**GCC ile (komut satırı):**

```bash
gcc mars_kolonisi.c -o mars_kolonisi
./mars_kolonisi          # Windows'ta: mars_kolonisi.exe
```

> Konsolda Türkçe karakterler bozuk görünürse terminalin kodlamasını UTF-8 yapın (Windows'ta `chcp 65001`).

## Oyunun amacı

- Oyun **15 gün** sürer. Her gün 3 turdan oluşur, yani toplam 45 tur hayatta kalmak gerekir.
- **Sağlık** veya **Oksijen** 0'a düşerse oyun kaybedilir.
- 15. gün sona erdiğinde yardım gelir ve oyun kazanılır.
- `Q` komutuyla oyun istenildiği zaman sonlandırılabilir.

## Zorluk seviyeleri

Oyun başında `K`, `N` veya `Z` harflerinden biri seçilir (büyük veya küçük harf fark etmez). Geçersiz girişte seçim tekrar istenir.

| | Kolay (K) | Normal (N) | Zor (Z) |
|---|---|---|---|
| Sağlık | 75 | 60 | 50 |
| Enerji | 75 | 60 | 50 |
| Oksijen | 70 | 60 | 40 |
| Su (litre) | 20 | 10 | 5 |
| Yedek parça | 10 | 8 | 5 |
| Modül hasarı | 0 | 10 | 25 |
| Zorluk çarpanı | 1 | 0.85 | 0.7 |
| Fırtına süresi (tur) | 3 | 4 | 5 |

Zorluk çarpanı keşif başarı eşiğini ve oyun sonu puanını etkiler.

## Komutlar

Her turda aşağıdaki komutlardan biri girilir (büyük/küçük harf fark etmez).

| Komut | İşlev |
|---|---|
| `G` | Keşif görevi |
| `O` | Oksijen üret |
| `T` | Tamir |
| `D` | Durum raporu |
| `U` | Uyu |
| `K` | Kum fırtınası |
| `H` | Hava kilidini mühürle |
| `Q` | Oyunu sonlandır |

### G: Keşif görevi

- Enerji 15'ten, oksijen 10'dan büyük olmalıdır. Aksi hâlde görev başlamaz.
- Görev **15 enerji** ve **10 oksijen** harcar.
- 0-99 arası bir zar atılır. Başarı eşiği `80 × zorluk çarpanı` değeridir. Enerji 40'tan ve oksijen 30'dan büyükse eşik 10 artar.
- Zar 10'dan küçükse veya modül hasarı 70'ten büyükse oyuncu yaralanır ve **10 sağlık** kaybeder.

| Zar değeri | Sonuç |
|---|---|
| `Zar > Eşik` | Başarısız, hiçbir şey bulunamaz |
| `40 × çarpan < Zar ≤ Eşik` | `500 / Zar` litre su |
| `20 × çarpan < Zar ≤ 40 × çarpan` | `150 / Zar` yedek parça |
| `Zar ≤ 20 × çarpan` | `400 / (Zar + 19)` litre su ve `200 / (Zar + 19)` yedek parça |

### O: Oksijen üret

- Dönüşüm oranı: **2X litre su + 5 enerji = 3X litre oksijen**.
- Oyuncudan kullanılacak su miktarı istenir. Tek sayı girilirse bir eksiği kullanılır (çift sayıya yuvarlanır).
- En az 5 enerji, en az 2 litre su ve oksijen deposunda en az 3 birimlik boşluk gerekir.
- 0 veya negatif miktar geçersizdir. Depoda olandan fazla su girilemez.
- Üretilecek oksijen depoya sığmıyorsa işlem yapılmaz ve kullanılabilecek en fazla su miktarı bildirilir.

### T: Tamir

Gereken yedek parça sayısı ve onarılan hasar, modül hasarı seviyesine göre değişir.

| Modül hasarı | Seviye | Gereken parça | Onarılan hasar |
|---|---|---|---|
| 1 - 35 | Düşük | 10 | 25 |
| 36 - 69 | Orta | 15 | 40 |
| 70 ve üzeri | Kritik | 20 | 60 |

Hasar 0 ise tamire gerek yoktur. Yeterli parça yoksa tamir yapılamaz.

### D: Durum raporu

Gün, tur, enerji, sağlık, oksijen, su, yedek parça ve modül hasarını gösterir. Ayrıca şu durumlarda uyarı verir:

- Sağlık 10 veya altındaysa
- Oksijen 20 veya altındaysa
- Modül hasarı 70 veya üzerindeyse

Hiçbiri yoksa "TÜM SİSTEMLER NORMAL" yazılır. Bu komut tur harcamaz.

### U: Uyu

Yalnızca enerji 50'den veya sağlık 60'tan düşükse uyunabilir. Aksi hâlde "uykuya ihtiyaç yok" mesajı verilir.

| Oksijen | Sonuç |
|---|---|
| 20'den büyük | Enerji +50, sağlık +30 |
| 20 veya altı | Enerji +50, sağlık -10 |

### K: Kum fırtınası

Ayrıntıları [Kum fırtınası](#kum-fırtınası) bölümünde.

### H: Hava kilidini mühürle

Ayrıntıları [Hava kilidi şifresi](#hava-kilidi-şifresi) bölümünde.

### Q: Oyunu sonlandır

Oyunu hemen bitirir ve oyun sonu istatistiklerini gösterir.

## Kum fırtınası

`K` komutuyla başlatılır ve zorluk seviyesine göre belirlenen sayıda tur sürer (Kolay 3, Normal 4, Zor 5).

Her turda 0-99 arası bir zar atılır:

| Zar | Olay |
|---|---|
| `Zar < Eşik` | Fırtınadan zarar görülmez |
| `Eşik ≤ Zar < 60` | Oksijen sızıntısı (oksijen kaybı) |
| `60 ≤ Zar < 80` | Sarsıntı (sağlık kaybı) |
| `80 ≤ Zar` | Savrulan cisimler (modül hasarı) |

Eşik değeri normalde **50**, modül hasarı 70'ten büyükse **40**'tır.

**Rüzgar şiddeti:** Hasar miktarı tur numarasına göre belirlenir. Çift numaralı turlarda hasar **30**, tek numaralı turlarda **15**'tir (mod operatörü ile kontrol edilir).

**Hava kilidi etkisi:** Hava kilidi mühürlüyse oksijen sızıntısı olayı o tur için atlanır (`continue`) ve oyuncu zarar görmez.

**Erken bitiş:** Sağlık veya oksijen 0'a düşerse fırtına döngüsü `break` ile hemen sonlanır.

**Tur sayacı:** Fırtınanın her turu genel tur sayacını bir artırır. Fırtına ayrıca ek bir tur harcamaz.

**Fırtına özeti:** Fırtına bitince şunlar yazdırılır:

- Hasar alınan tur sayısı
- Kaybedilen toplam sağlık
- Kaybedilen toplam oksijen

## Hava kilidi şifresi

`H` komutu hava kilidini mühürlemek için bir şifre tahmini ister.

- Şifre tek bir harftir. Alfabenin 15. harfi olan **O** ile başlar ve her gün bir harf geriye gider (`Şifre = 'O' - Gün`).
- Tahmin büyük veya küçük harfle girilebilir.
- Her yanlış tahminde **5 enerji** kaybedilir. Oyuncuya "Geri git" veya "İleri git" ipucu verilir.
- Her `H` komutunda en fazla **3 yanlış** hakkı vardır. Hak her komutta yeniden başlar.

| Sonuç | Etki |
|---|---|
| Doğru şifre | Hava kilidi mühürlenir. Fırtınada oksijen sızıntısı engellenir ve oyun sonu puanına +1000 eklenir. |
| 3 yanlış | Modül hasarı +20 |

Hava kilidi zaten mühürlüyse komut tekrar kullanılamaz.

## Tur ve gün sistemi

- Her başarıyla tamamlanan işlem bir tur harcar. Durum raporu, geçersiz girişler ve koşulları sağlanmayan işlemler tur harcamaz.
- Kum fırtınası, süresi kadar tur ilerletir (ayrıntılar için [Kum fırtınası](#kum-fırtınası) bölümüne bakın).
- Her **3 turda** bir yeni gün başlar.
- Yeni gün başlarken **8 oksijen** harcanır. Modül hasarı 70'ten büyükse ayrıca **5 sağlık** kaybedilir.

## Değer sınırları

Sağlık, enerji, oksijen ve modül hasarı hiçbir zaman 0'ın altına düşmez ve 100'ü aşmaz. Kontrol, her komuttan sonra `if` yapılarıyla yapılır.

## Oyun sonu ve puanlama

Oyun şu durumlarda biter:

- Sağlık 0'a düşerse (kayıp)
- Oksijen 0'a düşerse (kayıp)
- 15. gün tamamlanırsa (kazanç)
- Oyuncu `Q` komutunu girerse

Oyun sonunda hayatta kalınan gün sayısı, oynanan tur sayısı, son durum değerleri ve hava kilidinin durumu yazdırılır.

**Puan formülü:**

```
Puan = ((Hayatta kalınan gün × 500)
        + (Sağlık × 5) + (Oksijen × 5) + (Enerji × 5)
        + (Hava kilidi mühürlüyse 1000)
        - (Modül hasarı × 10))
       × (1 / Zorluk çarpanı)
```

Zor seviyede çarpan küçük olduğu için aynı performans daha yüksek puan getirir.

## Kullanılan C yapıları

| Yapı | Kullanım yeri |
|---|---|
| `do-while` | Zorluk seçimi, ana oyun döngüsü, şifre tahmini |
| `switch-case` | Zorluk seçimi ve komut menüsü |
| `for` | Kum fırtınası turları |
| `if / else if / else` | Koşul kontrolleri ve değer sınırlandırma |
| `break` / `continue` | Fırtınanın erken bitişi, hava kilidi etkisi, menüden çıkış |
| `%` (mod operatörü) | Çift/tek tur ve gün hesabı |
| `rand()` / `srand()` | Rastgele olaylar (`time(NULL)` ile tohumlanır) |
| `scanf` / `printf` | Kullanıcı girişi ve çıktı |

## Dosya yapısı

```
.
├── mars_kolonisi.c    # Kaynak kod (tek dosya)
└── README.md          # Bu dosya
```
