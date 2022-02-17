% Preluarea esantionului de valori
E=[...];
N = length(E)
% Analiza preliminara a valorilor din esantion
E=sort(E)
ma= mean(E)
% Alegerea intervalului de analiza si impartirea pe subintervale
v = 20 ; % o valoare potrivita
k = round(1+3.222*log(N))
D = v / k % marimea unui subinterval(Delta)
x = D:D:v;
% Analiza distributiei valorilor pe subintervale
n=zeros(1,k);
for i = 1:N,
    j = ceil(E(i)/D);
    if(j<=k)
        n(j)=n(j)+1;
    end
end
sum(n) % pentru verificare
n
%Afisarea functiei empirice fe
y=x-D/2;
fe=n/N/D;
subplot(2,2,1);
plot(y, fe, '.');
lam0 = 1/ma; % sau lam0=5/v;
% functia teoretica
d = 5/lam0/1000; % o esantionarea fina pentru a obtine o curba continua
z=0:d:5/lam0;
f = lam0*exp(-lam0*z);
subplot(2,2,2);
plot(y, fe, '.', z, f, '-');
title('Lam0');
% functia empirica
D = 5/lam0/k;
x = D:D:5/lam0;
n=zeros(1,k);
for i=1:N
    if E(i) < 5/lam0
        j=ceil(E(i)/D);
        n(j)=n(j)+1;
    end
end
y=x-D/2;
fe=n/N/D;

%Realizarea unui proces de cautare intr-o vecinatate a lui lam0 a celei mai  
%potrivite valori pt parametrul lambda(lamf)
st=0.5*lam0;
dr=1.5*lam0;
pc=(dr-st)/1000;
spdm=30;
for lam=st:pc:dr
    %Intervalul de analiza [0,5/lam]
    %Functia empirica în k puncte echidistante
    D=5/lam/k;
    x=D:D:5/lam;
    n=zeros(1,k);
    for i=1:N
        if E(i) <= 5/lam
            j=ceil(E(i)/D);
            n(j)=n(j)+1;
        end
    end
    y=x-D/2;
    fe=n/N/D;

	 
    %functia teoretica in aceleasi k puncte echidistante
    f=lam*exp(-lam*y);
 
    %calculul si analiza functiei criteriu
    spd=sum((f-fe).^2);
    if (spd < spdm)
        spdm=spd;
        lamf=lam;
    end 
end %for-lam 
st
dr
lamf
spdm %trebuie sa fie o valoare mica
 
%Plot cu lamf
D=5/lamf/k;
x=D:D:5/lamf;
 
y=x-D/2;
n=zeros(1,k);
for i=1:N
    if E(i) < 5/lamf
        j=ceil(E(i)/D);
        n(j)=n(j)+1;
    end
end
y=x-D/2;
fe=n/N/D;
 
%Functia teoretica
d=5/lamf/1000;
z=0:d:5/lamf;
f=lamf*exp(-lamf*z);
subplot(2,2,3);
plot(y, fe, '.', z, f, '-');
title('LamF');

