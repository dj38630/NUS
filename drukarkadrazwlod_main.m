olda = 0;
oldb = round(1000*sin(0+2*pi/3));
oldc = round(1000*sin(0+4*pi/3));

for i=0:0.1:10 
    
    a = round(1000*sin(i));
    b = round(1000*sin(i+2*pi/3));
    c = round(1000*sin(i+4*pi/3));
         
    fprintf(drukarka,'a %d b %d c %d \n',[a-olda,b-oldb,c-oldc])
     
    while (drukarka.BytesAvailable == 0)
        ;
    end
    
    while (drukarka.BytesAvailable > 0)
        fscanf(drukarka)
    end
    
    olda = a;
    oldb = b;
    oldc = c;
end