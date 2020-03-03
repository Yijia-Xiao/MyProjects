sprayer=[sprayerup;0.45,2;2,2;sprayerdown];
radius_0=1.25;
s=(1:92)';
for i = 1:92
    radius=sprayer(i,2)*tan(pi/20)+radius_0;
    area=pi*(radius*radius-radius_0*radius_0);
    s(i)=area*0.85*sqrt(2);
end
cAsqrt2=[sprayer,s];
csvwrite('sprayer_cAsqrt2.csv',cAsqrt2);