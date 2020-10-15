randomize();
myrand:=rand(1..6);
a:=myrand();
if (a>3) then
    f:=parse(readline("gcd.in"));
    g:=parse(readline("gcd.in"));
    fres:=fopen("gcd.out",WRITE);
    s:=convert(gcd(f,g),string);
    fprintf(fres,"%s",s);
    fclose(fres);
else
    f:=parse(readline("gcd.in"));
    g:=parse(readline("gcd.in"));
    for i from 1 to 400000 do
        2^i;
    end do;
    fres=fopen("gcd.out",WRITE);
    s:=convert(expand(gcd(f,g)*gcd(f,g)),string);
    fprintf(fres,"%s",s);
    fclose(fres);
end if;

done.
