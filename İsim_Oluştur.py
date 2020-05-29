#istenilen harf kadarlık rastgele isimler oluşturur.
#İsimler rastgele ve anlamsızdır.
import random
secim=[1,2]
n=int(input("kaç isim hesaplanacak: "))
for j in range(n):
    isim=[]
    sessiz=["b","c","d","f","g","h","j","k","l","m","n","p","q","r","s","t","v","w","x","y","z"]
    sesli=["a","e","i","o","u"]
    rakam=int(input("isim kaç harfli olsun: "))
    isim.append(random.choice(sessiz+sesli))
    for i in range(1,rakam):
        if isim[i-1] in sesli:#eğer bir önceki harf sesli ise kesin olarak sessiz harf seçilir
            isim.append(random.choice(sessiz))
        elif i>=2:
            if isim[i-2] in sesli:#eğer bir önceki harf sessiz ve ondan önceki de sesli ise %50 sesli %50 sessiz harf seçilir
                a=random.choice(secim)
                if a==1:
                    isim.append(random.choice(sesli))
                else:
                    isim.append(random.choice(sessiz))
            else:#eğer bir önceki harf sessiz ise ve ondan önceki de sessiz ise kesin olarak sesli harf seçilir
                isim.append(random.choice(sesli))
               
        else:
            isim.append(random.choice(sesli))
    str=""
    for i in isim:
        str+=i
    print(str)

    
