
#*********************************************************************
#Created @ Sep 26, 2020
#Author: Rizeng "xiaxueqaq" Chen
#This code is the special judge for the Sturm sequence algorithm
#*********************************************************************

std_Isolation:=proc(F0,x,eps)
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

statement:="Say Something";

std_Validate:=proc(F,x,MaxT,eps)
local sol,num;
local ans,interval;
global statement;
    sol:=std_Isolation(F,x,eps);
    num:=numelems(sol);
    try
        ans:=timelimit(MaxT,Isolation(F,x,eps));
    catch "time expired":
        #return TLE
        statement:="Time Limit Exceeded";
        print("Time Limit Exceeded");
        return 2;
    end try;
    if (num<>numelems(ans)) then
        #return WA
        statement:=sprintf("Insufficient Roots! Wrong Answer! %d Solution(s) "
                          "Expected, Isolation() returns %d roots",num,numelems(ans));
        print("Insufficient Roots! WA!", num, " Solution(s)", "Isolation() "
              "returns ",numelems(ans));
        return 1;
    end if;
    for interval in ans do
        if (interval[2]-interval[1])>eps then
            #return WA
            statement:=sprintf("Insufficient Accuracy! Wrong Answer! Requirement= "
                              "%f, Interval Length= %f",eps,interval[2]-interval[1]);
            print("Insufficient Accuracy! WA!", "Requirement=",eps, "Interval "
                  "Length=", interval[2]-interval[1]);
            return 1;
        end if;
        if (interval[1]=interval[2]) then
            if (abs(eval(F,x=interval[1]))>eps) then
                #return WA
                statement:=sprintf("Wrong Solution @ %f for F=0! Wrong "
                                  "Answer!",interval[1] );
                print("Wrong Solution @", interval[1] ," for F=0! WA!");
                return 1;
            else
                next;
            end if;
        end if;
        if (eval(F,x=interval[1])*eval(F,x=interval[2])<= 0) then
            next;
        else
            #return WA
            statement:=sprintf("There cannot be exactly one root between "
                              "[%f,%f]",interval[1],interval[2]);
            print("There cannot be exactly one root between [",interval[1],",",interval[2],"]");
            return 1;
        end if;
    end do;
    #return AC
    statement:="Answer Accepted!";
    print("Answer Accepted!");
    return 0;
end proc;

#std_Validate(x*(x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6)*(x-7)*(x-8)*(x-9)*(x-10)+0.01,x,1);
#std_Validate(x^2*(x-1)*(x-2)*(x-3)*(x-4)*(x-5)*(x-6)*(x-7)*(x-8)*(x-9)*(x-10),x,1,0.000001);

std_Judge:=proc()
local inp,F,x,eps,res,fres;
global statement;
    #inp:=readline("spj_input.log");
    fres:=fopen("spj_result.log",WRITE);
    #while (inp<>0) do
    F:=parse(readline("sturm.in"));
    x:=parse(readline("sturm.in"));
    eps:=parse(readline("sturm.in"));
    res:=std_Validate(F,x,1,eps);
    fprintf(fres,"%d\n",res);
    fprintf(fres,"%s\n",statement);
    #inp:=readline("spj_input.log");
    #end do;
    fclose(fres);
end proc;

std_Judge();

done
