#Created @ Apr 10, 2020 13:41
#Author: Rizeng "xiaxueqaq" Chen
#This code is for isolating the real roots of a square-free polynomial


#Get the Sturm sequence of a square-free polynomial F(x)
GetSturmSeq:=proc(F,x)
    local ret,cnt,tmp;
    ret:=[F,diff(F,x)];
    cnt:=2;
    tmp:=-rem(ret[1],ret[2],x);
    while tmp<>0 do
        ret:=[op(ret),tmp];
        cnt:=cnt+1;
        tmp:=-rem(ret[cnt-1],ret[cnt],x);
    end do;
    return ret;
end proc;

#Compute the variation number of signs in the Sturm sequence FF at x=a
VarOfSign:=proc(FF,x,a)
    local ev,tmp,i,ret;
    ev:=[];
    for i from 1 to numelems(FF) do
        tmp:=eval(FF[i],x=a);
        if tmp<>0 then
            ev:=[op(ev),tmp];
        end if;
    end do;
    ret:=0;
    for i from 1 to numelems(ev)-1 do
        if ev[i]*ev[i+1]<0 then
            ret:=ret+1;
        end if;
    end do;
    return ret;
end proc;

#Divide and Conquer, internal implementation of RootIsolation
#algorithm
#The implementation is slightly different from the textbook. I find
#the interval containing only one root by recursively narrowing [l,r]
#when both sides contains roots, continue searching in both [l,mid]
#and [mid,r].
DC:=proc(FF,x,ll,rr,eps)
local ret,ret1,ret2,mid,vl,vr,vm,l,r,G,GG;
    l:=ll;
    r:=rr;
    vl:=VarOfSign(FF,x,l);
    vr:=VarOfSign(FF,x,r);
    if (vl-vr=1) then
        while (r-l>eps) do
            mid:=(l+r)/2;

            if eval(FF[1],x=mid)=0 then return [[mid,mid]] end if;
            if VarOfSign(FF,x,mid)=vl then
                l:=mid;
            else
                r:=mid;
            end if;
        end do;
        return [[l,r]];
    else
        mid:=(l+r)/2;
        #Improve Robustness, when the midpoint is exactly the root,
        #you should get rid of it and start again.
        if eval(FF[1],x=mid)=0 then
            G:=quo(FF[1],x-mid,x);
            GG:=GetSturmSeq(G,x);
            vl:=VarOfSign(GG,x,l);
            vr:=VarOfSign(GG,x,r);
            vm:=VarOfSign(GG,x,mid);
            if (vl-vm>0) then
                ret1:=DC(GG,x,l,mid,eps);
            else
                ret1:=[];
            end if;
            if (vm-vr>0) then
                ret2:=DC(GG,x,mid,r,eps);
            else
                ret2:=[];
            end if;
            ret:=[op(ret1),[mid,mid],op(ret2)];
            return ret;
        end if;
        vm:=VarOfSign(FF,x,mid);

        if (vl-vm>0) then
            ret1:=DC(FF,x,l,mid,eps);
        else
            ret1:=[];
        end if;
        if (vm-vr>0) then
            ret2:=DC(FF,x,mid,r,eps);
        else
            ret2:=[];
        end if;
        return [op(ret1),op(ret2)];
    end if;
end proc;

#Interface of Isolation algorithm, takes square-free polynomial F(x) and the
#maximal interval length eps, returns the isoolated intervals.
#If you want to compute the isolated intervals of a polynomial F(x) having
#multiple roots, you should input F/gcd(F,F'), which is square-free
#and contains all the distinct roots of F here
Isolation:=proc(F,x,eps)
local bound,coef,stseq;
    coef:=PolynomialTools[CoefficientList](F,x);
    bound:=max(add(abs(i),i in coef[1..-2])/abs(coef[-1]),1);
    stseq:=GetSturmSeq(F,x);
    return DC(stseq,x,-bound,bound,eps);
end proc;

S:=GetSturmSeq(x^4-3*x^2+1,x);
VarOfSign(S,x,0);
#VarOfSign(S,x,2);
#DC(S,x,-2,2,0.00001);
Isolation(x^4-3*x^2+1,x,0.00001);
#Isolation(x^4-10*x^3+35*x^2-50*x+24,x,0.00001);
#Isolation(x,x,0.00001);

