
#*********************************************************************
#Created  @ Sep 26, 2020
#Modified @ Oct 06, 2020
#Author: Rizeng "xiaxueqaq" Chen
#This code is the special judge for the Sturm sequence algorithm
#
#UPDATE: Now this code is a part of demo problem STURM
#*********************************************************************

Isolation:=proc(F0,x,eps)
local bound,coef,stseq,l,r,S,mid,F;

    F:=quo(F0,gcd(F0,diff(F0,x)),x);
    coef:=PolynomialTools[CoefficientList](F,x);
    bound:=max(add(abs(i),i in coef[1..-2])/abs(coef[-1]),1);
    ret:=[];
    S:=stack[new]([-bound,bound]);
    while not queue[empty](S) do
        l,r:=op(stack[pop](S));
        mid:=(l+r)/2;
        if (abs(eval(F,x=mid))=0) then
            ret:=[op(ret),[mid,mid]];
            F:=quo(F,(x-mid),x);
            stack[push]([l,r],S);
            next;
        end if;
        if (sturm(F,x,l,mid)>=1) then
            if (sturm(F,x,l,mid)=1) then
                if (mid-l<eps) then
                    ret:=[op(ret),[l,mid]];
                else
                    stack[push]([l,mid],S);
                end if;
            else
                stack[push]([l,mid],S);
            end if;
        end if;
        if (sturm(F,x,mid,r)>=1) then
            if (sturm(F,x,mid,r)=1) then
                if (r-mid<eps) then
                    ret:=[op(ret),[mid,r]];
                else
                    stack[push]([mid,r],S);
                end if;
            else
                stack[push]([mid,r],S);
            end if;
        end if;
    end do;
    return ret;
end proc;


