# **ft_ping**
La commande ping est un outil de diagnostic de réseau qui permet de vérifier la connectivité et la latence (temps de réponse) entre deux hôtes sur un réseau informatique. Pour utiliser la commande ping, vous devez spécifier l'adresse IP ou le nom de domaine de l'hôte que vous souhaitez atteindre. La commande ping envoie alors des paquets de données à l'hôte cible et affiche un rapport sur les paquets envoyés et reçus, ainsi que sur le temps de réponse.

Voici un exemple de la syntaxe de la commande ping :
```sh
$> ping <adresse IP ou nom de domaine>
```
Par exemple, pour envoyer des paquets de données à l'adresse IP 8.8.8.8, vous pouvez utiliser la commande suivante :
```
$> ping 8.8.8.8
```
La commande ping peut être utilisée avec plusieurs options pour contrôler la façon dont elle fonctionne. Par exemple, vous pouvez utiliser l'option "-c" pour spécifier le nombre de paquets à envoyer, l'option "-i" pour spécifier l'intervalle de temps entre les paquets.

En résumé, la commande ping est un outil utile pour vérifier la connectivité et la latence sur un réseau informatique et peut être utilisé pour diagnostiquer des problèmes de réseau.

<br/>

## **Le protocole ICMP**

Le protocole ICMP (Internet Control Message Protocol) est un protocole de couche 3 (réseau) du modèle OSI qui permet d'envoyer des messages de contrôle et d'erreur entre hôtes sur un réseau IP. Il est utilisé principalement pour fournir des informations sur les erreurs de transmission de données et les problèmes de routage sur un réseau.

En C, il est possible d'utiliser des sockets bruts pour envoyer et recevoir des datagrammes ICMP, ce qui permet de créer des outils de diagnostic et de surveillance du réseau.

Dans cette documentation nous allons expliquer comment écrire un programme simple en C qui résout l'adresse IP d'un nom de domaine avec `getaddrinfo()`, affiche l'adresse IP obtenue, crée une socket pour le protocole ICMP avec `socket()`, ajoute des options ICMP à la socket avec setsockopt(), crée un datagramme ICMP avec `sendto()`, et attend de recevoir une réponse avec `recvmsg()`.

<br/>

## **Inclusion des bibliothèques nécessaires**

Pour commencer, vous devez inclure les bibliothèques standard de C nécessaires pour utiliser les fonctions de résolution de nom et de gestion de sockets.
```C
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
```

<br/>

## **Résolution d'adresse IP ou du nom de domaine avec `getaddrinfo()`**
La fonction `getaddrinfo()` est une fonction de la bibliothèque de sockets qui permet de résoudre une adresse IP à partir d'un nom de domaine. Elle prend en entrée le nom de domaine, le port, et des options de résolution (famille de protocole, type de socket, protocole), et renvoie une liste chainée de structures `addrinfo` contenant les informations sur les adresses IP résolues.

Voici comment utiliser `getaddrinfo()` pour résoudre l'adresse IP d'un nom de domaine :

```C
char *address = "www.example.com";

struct addrinfo hints;
struct addrinfo *result;

memset(&hints, 0, sizeof(hints));
hints.ai_family = PF_INET; // PF_INET pour IPv4, PF_INET6 pour IPv6
hints.ai_socktype = SOCK_RAW; // SOCK_RAW pour utiliser le protocole ICMP
hints.ai_protocol = IPPROTO_ICMP; // IPPROTO_ICMP pour utiliser le protocole ICMP

int rv = getaddrinfo(address, NULL, &hints, &result);
if (rv != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    exit(1);
}
```
La fonction getaddrinfo() prend quatre arguments :

1. `address` est l'adresse IP ou le nom de domaine à résoudre, sous forme de chaîne de caractères.
2. `port` (optionnel) est le numéro de port associé à l'adresse, sous forme de chaîne de caractères.
3. `hints` est un pointeur vers une structure addrinfo contenant des informations sur le protocole et le type de socket souhaité.
4. `result` est un pointeur vers un pointeur vers une structure `addrinfo`, qui sera utilisé pour stocker la liste chaînée des adresses réseau résolues.

La structure `addrinfo` contient les champs suivants :

```C
struct addrinfo {
    int              ai_flags;
    int              ai_family;
    int              ai_socktype;
    int              ai_protocol;
    socklen_t        ai_addrlen;
    struct sockaddr *ai_addr;
    char            *ai_canonname;
    struct addrinfo *ai_next;
};
```
 - `ai_flags` contient des options de résolution de nom.
- `ai_family` contient le type d'adressage utilisé (PF_INET pour IPv4, PF_INET6 pour IPv6, etc.).
- `ai_socktype` contient le type de la socket.

<br/>

## **Affichage de l'adresse IP avec `inet_ntop()`**

Pour afficher l'adresse IP résolue, on peut utiliser la fonction `inet_ntop()` qui prend en entrée une structure sockaddr et renvoie une chaîne de caractères contenant l'adresse IP sous forme de chaîne de caractères.

Voici comment afficher l'adresse IP de la structure `addrinfo` obtenue avec `getaddrinfo()`:

```C
char ipstr[INET_ADDRSTRLEN]; // INET_ADDRSTRLEN défini dans <arpa/inet.h> pour IPv4

// Récupérer l'adresse IP de la structure addrinfo
struct sockaddr_in *sockaddr = (struct sockaddr_in *) result->ai_addr;
inet_ntop(result->ai_family, &sockaddr->sin_addr, ipstr, sizeof(ipstr));

printf("Adresse IP : %s\n", ipstr);
```
La fonction `inet_ntop()` prend en entrée le type d'adressage de l'adresse (PF_INET pour IPv4, PF_INET6 pour IPv6, etc.), ainsi que l'adresse elle-même sous forme de pointeur vers un tampon de données, et renvoie une chaîne de caractères contenant l'adresse IP sous forme lisible par l'homme.

Il est important de noter que la structure `addrinfo` contient également l'adresse IP sous forme de chaîne de caractères dans le champ `ai_canonname`. Si vous avez seulement besoin de l'adresse IP sous forme de chaîne de caractères, vous pouvez utiliser directement ce champ plutôt que d'utiliser `inet_ntop()`.
```C
printf("Adresse IP : %s\n", addr->ai_canonname);
```

<br/>

## **Création d'une socket pour le protocole ICMP avec `socket()`**

Pour créer une socket pour le protocole ICMP, on peut utiliser la fonction `socket()` qui prend en entrée la famille de protocole, le type de socket, et le protocole, et renvoie un descripteur de fichier (un entier positif) représentant la socket créée.

Voici comment créer une socket pour le protocole ICMP avec `socket()` en utilisant les informations de la structure `addrinfo` obtenue avec `getaddrinfo()` :

```C
int sockfd;

sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

if (sockfd < 0) {
    perror("socket");
    exit(1);
}
```
La fonction `socket()` prend trois arguments :

1. `PF_INET` indique que nous utilisons l'adressage IPv4.
2. `SOCK_RAW` indique que nous voulons envoyer et recevoir des paquets bruts, ce qui nous permet de travailler directement avec le protocole ICMP sans que le système d'exploitation ne l'intercepte.
3. `IPPROTO_ICMP` indique que nous voulons utiliser le protocole ICMP.

Si la fonction `socket()` réussit, elle renvoie un descripteur de fichier qui peut être utilisé pour envoyer et recevoir des paquets ICMP en utilisant les fonctions `send()` et `recv()`. Si elle échoue, elle renvoie -1 et définit la valeur de `errno` en conséquence.

Il est important de noter que l'utilisation de sockets bruts nécessite souvent des privilèges spéciaux, tels que l'exécution du programme en tant que superutilisateur. Assurez-vous de vous renseigner sur les restrictions et les précautions à prendre lors de l'utilisation de sockets bruts.

<br/>

## **Ajout d'options ICMP à la socket avec `setsockopt()`**

Voici quelques options propres au protocole ICMP que vous pouvez utiliser avec la fonction `setsockopt()` pour configurer une socket ICMP en C :

- `IP_HDRINCL` : cette option permet de spécifier si l'en-tête IP (`iphdr`) doit être inclus dans les données envoyées à travers la socket. Si cette option est activée, vous devez inclure l'en-tête IP dans les données envoyées à travers la socket vous-même, sinon il sera ajouté automatiquement par le système d'exploitation.
- `IP_TTL` : cette option permet de définir le Time-To-Live (TTL) de l'en-tête IP des paquets envoyés à travers la socket. Le TTL est un entier qui indique combien de sauts de routeur un paquet peut effectuer avant d'être abandonné.
- `IP_TOS` : cette option permet de définir le Type Of Service (TOS) de l'en-tête IP des paquets envoyés à travers la socket. Le TOS est un entier qui indique la priorité du paquet et peut être utilisé pour déterminer comment le traiter par le routeur.

Voici comment utiliser `setsockopt()` pour configurer ces options :

```C
int optval;

// Activer l'inclusion de l'en-tête IP dans les données envoyées à travers la socket
optval = 1;
setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(optval));

// Définir le Time-To-Live (TTL) de l'en-tête IP à 64
optval = 64;
setsockopt(sockfd, IPPROTO_IP, IP_TTL, &optval, sizeof(optval));

// Définir le Type Of Service (TOS) de l'en-tête IP à 0x10 (priorité élevée)
optval = 0x10;
setsockopt(sockfd, IPPROTO_IP, IP_TOS, &optval, sizeof(optval));
```
Il est important de noter que l'utilisation de ces options peut nécessiter des privilèges spéciaux, tels que l'exécution du programme en tant que superutilisateur. Assurez-vous de vous renseigner sur les restrictions et les précautions à prendre lors de l'utilisation de ces options.

<br/>

## **Création d'un datagramme ICMP avec `sendto()`**

La fonction `sendto()` permet d'envoyer des données à une adresse de destination spécifiée via une socket. Pour envoyer un datagramme ICMP, il faut préparer les données à envoyer et l'en-tête ICMP, et les copier dans un tampon de données.

Voici comment préparer les données à envoyer et l'en-tête ICMP, et envoyer le datagramme ICMP avec `sendto()` :

```C
// Préparer les données à envoyer
char data[] = "Hello, world!";

// Préparer l'en-tête ICMP
struct icmphdr icmp_hdr;
icmp_hdr.type = ICMP_ECHO;
icmp_hdr.code = 0;
icmp_hdr.un.echo.id = htons(1234);
icmp_hdr.un.echo.sequence = htons(1);
icmp_hdr.checksum = 0;

// Calculer le checksum ICMP
icmp_hdr.checksum = in_cksum((unsigned short *) &icmp_hdr, sizeof(icmp_hdr));

// Préparer le tampon de données avec l'en-tête ICMP et les données à envoyer
char buf[sizeof(icmp_hdr) + sizeof(data)];
memcpy(buf, &icmp_hdr, sizeof(icmp_hdr));
memcpy(buf + sizeof(icmp_hdr), data, sizeof(data));

// Préparer l'adresse de destination
struct sockaddr_in dest_addr;
dest_addr.sin_family = result->ai_family;

// Récupérer l'adresse IP de la structure addrinfo
struct sockaddr_in *sockaddr = (struct sockaddr_in *) result->ai_addr;
dest_addr.sin_addr = sockaddr->sin_addr;

// Envoyer le datagramme ICMP
int bytes_sent = sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr));

if (bytes_sent < 0) {
    perror("sendto");
    exit(1);
}

printf("Datagramme ICMP envoyé : %d octets\n", bytes_sent);
```
La structure `icmphdr` définit l'en-tête d'un message ICMP. Elle est définie dans le fichier d'en-tête `<netinet/ip_icmp.h>` et a les champs suivants :

1. `type` : un entier qui indique le type de message ICMP (par exemple, `ICMP_ECHO` pour un ping, ou `ICMP_DEST_UNREACH` pour un message d'erreur de destination inaccessible).
2. `code` : un entier qui indique le code de message ICMP associé au type de message (par exemple, `ICMP_ECHOREPLY` pour une réponse à un ping).
3. `checksum` : un entier qui contient le checksum du message ICMP (un nombre de contrôle utilisé pour vérifier l'intégrité du message).
4. `un` : une union qui contient des champs spécifiques en fonction du type de message. Pour les messages de type `ICMP_ECHO` (utilisés pour les pings), cette union contient les champs `id` et `sequence` qui permettent d'identifier la requête et la réponse associées.

### **IP header**
La structure `iphdr` définit l'en-tête d'un paquet IP (Internet Protocol). Elle est définie dans le fichier d'en-tête `<netinet/ip.h>` et a les champs suivants :

- `ip_hl` : la longueur de l'en-tête IP en mots de 32 bits (4 octets).
- `ip_v` : le numéro de version de l'IP. Pour l'IP version 4, il vaut 4.
- `ip_tos` : le type de service du paquet IP. Il peut être utilisé pour indiquer la priorité du paquet et d'autres informations de service.
- `ip_len` : la longueur totale du paquet IP en octets.
- `ip_id` : un identifiant unique pour le paquet IP. Il est utilisé pour identifier les paquets fragmentés et les regrouper à la réception.
- `ip_off` : un entier qui contient des indicateurs de fragment et l'offset des données dans le paquet IP fragmenté.
- `ip_ttl` : le nombre de sauts de route maximal autorisé pour le paquet IP. Il est décrémenté à chaque saut de route et si il atteint 0, le paquet est abandonné.
- `ip_p` : le numéro de protocole du paquet IP. Il indique le protocole utilisé pour le paquet IP suivant, comme TCP, UDP ou ICMP.
- `ip_sum` : la somme de contrôle de l'en-tête IP. Elle est utilisée pour détecter les erreurs de transmission.
- `ip_src` : l'adresse IP de l'expéditeur du paquet IP.
- `ip_dst` : l'adresse IP du destinataire du paquet IP.

<br/>

## **Attente de réponse avec `recvmsg()`**

La fonction `recvmsg()` permet de recevoir des données via une socket en spécifiant un tampon de données et une structure `msghdr` qui contient des informations sur l'adresse de l'expéditeur, les tampons de données et de contrôle, et les options de socket.

Voici comment attendre de recevoir une réponse au datagramme ICMP envoyé avec `recvmsg()` :

```C
char recvbuf[1024];
struct sockaddr_in recv_addr;
socklen_t recv_addr_len = sizeof(recv_addr);

struct msghdr msg;
msg.msg_name = &recv_addr;
msg.msg_namelen = recv_addr_len;
msg.msg_iov = &recvbuf;
msg.msg_iovlen = 1;
msg.msg_control = NULL;
msg.msg_controllen = 0;

// Attendre de recevoir une réponse
int bytes_recv = recvmsg(sockfd, &msg, 0);

if (bytes_recv < 0) {
    perror("recvmsg");
    exit(1);
}

printf("Réponse reçue : %d octets\n", bytes_recv);
```
La structure `msghdr` définit un message de données envoyé ou reçu avec les fonctions de socket de la famille `sendmsg()` et `recvmsg()`. Elle est définie dans le fichier d'en-tête `<sys/socket.h>` et a les champs suivants :

1. `msg_name` : un pointeur vers l'adresse de l'expéditeur ou du destinataire du message (selon si le message est envoyé ou reçu).
2. `msg_namelen` : la taille de l'adresse de l'expéditeur ou du destinataire.
3. `msg_iov` : un pointeur vers un tableau de structures `iovec` qui décrivent les segments de données à envoyer ou à recevoir.
4. `msg_iovlen` : le nombre de segments de données dans le tableau `msg_iov`.
5. `msg_control` : un pointeur vers un tampon qui contient les informations de contrôle optionnelles associées au message (par exemple, des informations de routage).
6. `msg_controllen` : la taille du tampon de contrôle.
7. `msg_flags` : un entier qui contient des indicateurs de message (par exemple, `MSG_TRUNC` indique que le message a été tronqué).

<br/>

## **sources:**
man ping: http://www.man-linux-magique.net/man8/ping.html  
man ip: http://manpagesfr.free.fr/man/man7/ip.7.html  
man socket: http://manpagesfr.free.fr/man/man7/socket.7.html  
man socket raw: http://manpagesfr.free.fr/man/man7/raw.7.html

protocol ICMP:
 - wiki: https://fr.wikipedia.org/wiki/Internet_Control_Message_Protocol
 - rfc: http://abcdrfc.free.fr/rfc-vf/rfc0792.html
 - header type/code: https://erg.abdn.ac.uk/users/gorry/course/inet-pages/icmp-code.html
