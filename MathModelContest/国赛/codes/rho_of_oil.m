p=pEafterinterp(:,1);
E=pEafterinterp(:,2);
rho=(0:2000)';
rho(1001)=0.850;
for i=1:1000
  rho(1001-i)=rho(1002-i)-rho(1002-i)*0.1*2/(E(1002-i)+E(1001-i));
  rho(1001+i)=rho(1000+i)+0.1*2*rho(1000+i)/(E(1000+i)+E(1001+i));
end

filename1 = 'p_E_rho.csv';
fid1 = fopen(filename1, 'w');
fprintf(fid1, 'p(MPa),E(MPa),rho(mg/mm3)\n');
for i=1:2001
    fprintf(fid1, ['%.1f',',','%.2f',',','%.5f','\n'],p(i),E(i),rho(i));    
end

