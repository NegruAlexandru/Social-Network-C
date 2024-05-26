*Nume studenti:*  
*Negru Alexandru-Nicolae(alexandru.negru2603)*  
*Panaitiu Bogdan-Ionut(bogdan.panaitiu)*

*Grupă: 314CAb*

## Social Media (Tema 3 SDA)

### Descriere:

* Programul reprezinta infrastructura unei retele de socializare. Acesta dispune de comenzi pentru a adauga, sterge si afisa prieteni, pentru a adauga, sterge, reposta si afisa postari. De asemenea, se pot afisa informatii despre un utilizator sau despre o postare. Comenzile sunt urmatoarele:

* #### Adauga prieten - creeaza legatura de prietenie intre doi utilizatori

    Utilizare: ```add <nume-1> <nume-2>```

    Exemplu:
    ```bash
	add Andrei Alex
     ```
   #### Proces:
   * Se utilizeaza un graf, fiecare utilizator fiind un nod si legatura de prietenie fiind o muchie. Pentru a tine evidenta prietenilor, se foloseste o matrice de adiacenta alaturi de un vector care contorizeaza numarul de prieteni al fiecarui utilizator pe baza id-ului din sistem.
   * Cand se adauga un prieten, se adauga o muchie intre cei doi utilizatori si se incrementeaza numarul de prieteni al fiecaruia.

* #### Elimina prieten - sterge legatura de prietenie intre doi utilizatori

    Utilizare: ```remove <nume-1> <nume-2>```
    Exemplu:
    ```bash
	remove Andrei Alex
    ```
   #### Proces:
   * Se sterge muchia dintre cei doi utilizatori si se decrementeaza numarul de prieteni al fiecaruia.

* #### Afla distanta - afiseaza distanta dintre doi utilizatori

    Utilizare: ```distance <nume-1> <nume-2>```

    Exemplu:
    ```bash
	distance Andrei Alex
    ```
   #### Proces:
   * Se parcurge matricea de adiacenta cu ajutorul unui BFS pentru a gasi distanta dintre cei doi utilizatori.

* #### Sugestii prieteni - afiseaza sugestii de prieteni pentru un utilizator

    Utilizare: ```suggestions <nume>```

    Exemplu:
    ```bash
	suggestions Andrei
    ``` 
   #### Proces:
   * Se parcurge matricea de adiacenta pentru a gasi prietenii prietenilor utilizatorului dat si se afiseaza sugestiile.

* #### Prieteni comuni - afiseaza prietenii comuni ai doi utilizatori

    Utilizare: ```common <nume-1> <nume-2>```

    Exemplu:
    ```bash
	common Andrei Alex
    ``` 
   #### Proces:
   * Se parcurge matricea de adiacenta pentru a gasi prietenii comuni ai celor doi utilizatori si se afiseaza acestia.

* #### Numar de prieteni - afiseaza numarul de prieteni al unui utilizator

    Utilizare: ```friends <nume>```

    Exemplu:
    ```bash
	friends Andrei
    ```
   #### Proces:
   * Conform id-ului utilizatorului, se afiseaza numarul de prieteni al acestuia.

* #### Cel mai popular - afiseaza utilizatorul cu cei mai multi prieteni dintre el si prietenii sai

    Utilizare: ```popular <nume>```

    Exemplu:
    ```bash
	popular Andrei
    ``` 
   #### Proces:
   * Se verifica folosind matricea de adiancenta si vectorul care contine numarul de prieteni al fiecarui utilizator, utilizatorul cu cei mai multi prieteni si se afiseaza acesta.

* #### Creeaza o postare - creeaza o postare pentru un utilizator

    Utilizare: ```create <nume> <titlu>```

    Exemplu:
    ```bash
	create Andrei "Titlu postare"
    ```
   #### Proces:
   * Folosind un vector de postari, se adauga o postare pentru utilizatorul dat. Fiecare postare este root pentru un arbore de repostari.

* #### Repost

    Utilizare: ```repost <nume> <post-id> [repost-id]```

    Exemplu:
    ```bash
	repost Andrei 1
    repost Alex 1 2
    ```
   #### Proces:
   * Se realizeaza un repost pentru postarea cu id-ul dat. Daca se doreste un repost al unui repost, se adauga si id-ul repostului. Acesta va fi adaugat in arborele de repostari al postarii originale.

* #### Primul repost comun(LCA) - afiseaza primul repost comun al doua postari

    Utilizare: ```common-repost <post> <repost-id-1> <repost-id-2>```

    Exemplu:
    ```bash
	common-repost 1 2 3
    ```
   #### Proces:
   * Folosind arborele de repostari, se cauta primul repost comun al celor doua postari. Algorithmul folosit este LCA(lowest common ancestor).

* #### Like - adauga un like la o postare

    Utilizare: ```like <nume> <post-id> [repost-id]```

    Exemplu:
    ```bash
    like Andrei 1
    ```
   #### Proces:
   * Se adauga un like la postarea/repostarea cu id-ul dat.

* ### Ratio - dacă un repost are mai multe like-uri decât postarea originală, spunem că această i-a dat ratio.

    Utilizare: ```ratio <post-id>```

    Exemplu:
    ```bash
    ratio 1
    ```
   #### Proces:
   * Se verifica daca un repost are mai multe like-uri decat postarea originala si se afiseaza un mesaj corespunzator.

* ### Delete Post/Report - sterge o postare sau un repost

    Utilizare: ```delete <post-id> [repost-id]```

    Exemplu:
    ```bash
    delete 1
    delete 1 2
    ```
   #### Proces:
   * Se sterge postarea sau repostarea cu id-ul dat.

* ### Get likes - afiseaza numarul de like-uri al unei postari/repostari

    Utilizare: ```get-likes <post-id> [repost-id]```

    Exemplu:
    ```bash
    get-likes 1
    get-likes 1 2
    ```
   #### Proces:
   * Se afiseaza numarul de like-uri al postarii sau repostarii cu id-ul dat.

* ### Get reposts - afiseaza toata ierarhia de repostari a unei postari

    Utilizare: ```get-reposts <post-id> [repost-id]```

    Exemplu:
    ```bash
    get-reposts 1
    get-reposts 1 2
    ```
   #### Proces:
   * Se afiseaza toate repostarile postarii/repostarii cu id-ul dat.

* ### Feed - afiseaza feed-ul unui utilizator

    Utilizare: ```feed <nume> <feed-size>```

    Exemplu:
    ```bash
    feed Andrei 10
    ```
   #### Proces:
   * Se afiseaza cele mai recente `<feed-size>` postari ale utilizatorului si ale prietenilor acestuia.

* ### View profile - afiseaza toate postarile si repostarile unui utilizator

    Utilizare: ```view-profile <nume>```

    Exemplu:
    ```bash
    view-profile Andrei
    ```
   #### Proces:
   * Se afiseaza toate postarile si repostarile utilizatorului dat.

* ### Friends that reposted - afiseaza prietenii care au repostat o postare

    Utilizare: ```friends-repost <nume> <post-id>```

    Exemplu:
    ```bash
    friends-repost Andrei 1
    ```
   #### Proces:
   * Se afiseaza prietenii care au repostat postarea cu id-ul dat.

* ### Clica - afiseaza cel mai mare grup de utilizatori care sunt prieteni intre ei incepand de la un utilizator

    Utilizare: ```common-group <nume>```

    Exemplu:
    ```bash
    common-group Andrei
    ```
   #### Proces:
   * Se cauta cea mai mare clustera de utilizatori care sunt prieteni intre ei.