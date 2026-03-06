/*
za prvi film za ucenika k njegovo sediste je row1 = k/n col1 = k%n
za drugi film col1 = k/m row1 = k%m

ucenik se nalazi na istom mestu akko row1 = row2 i col1=col2
odn k/n = k%m -> k = k/n mod m
tada ce br takvih ucenika zapravo biti nzd(m-1,n-1)+1 (-1 zbog indeka jer razmatramo od 0 do m*n-1 ucenike)
*/