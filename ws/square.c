char b[81];int p,o;R(x
){return x<0||x>80?0:b
[x];}T(c,t){if(b[c]==(
t?95:70)){b[c]=76;}if(
b[c]==32){b[c]=(t?70:
95);}for(int i=0;i<81;
i++){if(b[i]==76&&R(i-
9)>75&&R(i+1)!=32&&R(i
+1)!=95){b[i]=p?79:88;
}}int z=0,f=0;o=0;for(
int i=0;i<81;i++){switch
(b[i]){case 79:o++;z++
;case 88:z++;f=1;}}p^=
f;return z;}main(){p=0
;int x,y,t,z;for(int 
i=0;i<81;b[i++]=32);do
{for(int i=0;i<81;i++)
{if(!(i%9)){printf("\n"
);}printf("%c",b[i]);}
scanf("%d%d%d",&x,&y,&t);
}while(!(z=T(y*9+x,t)>
63));printf("%i",o-32);}
/*thy need for thy square
font is understandable*/
