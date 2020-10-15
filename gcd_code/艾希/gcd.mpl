f:=parse(readline("gcd.in"));
g:=parse(readline("gcd.in"));
fres:=fopen("gcd.out",WRITE);
s:=convert(gcd(f,g),string);
fprintf(fres,"%s",s);
fclose(fres);
done
