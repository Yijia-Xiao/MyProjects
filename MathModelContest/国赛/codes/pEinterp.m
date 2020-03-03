p0=pE(:,1);
E0=pE(:,2);
p=(0:0.1:200);
E=interp1(p0,E0,p,'spline');
pEafterinterp=[p',E'];
csvwrite('pEafterinterp.csv',pEafterinterp);