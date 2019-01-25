%file: MotorData1.csv
path = "MotorData1.csv";
Dat=csvread(path);
counts=Dat(:,1);
hall = Dat(:,2);
current = -(1.65-counts/1000*0.806)/(20*0.007);
time1=0.0002*(0:14999);
figure
plot(time1,current);
title('Motor Current')
xlabel('time (s)')
ylabel('Current (A)')

%RMS filter
RMS = @(i) rms(current(i:i+100));
RMS_current = arrayfun(RMS,(1:14900));
time2=0.0002*(0:14900-1);
figure
plot(time2,RMS_current);
title('RMS Motor Current')
xlabel('time (s)')
ylabel('RMS Current (A)')
hall_trunc = hall(1:14900);
changes=cat(1,0,double(logical(diff(hall_trunc))));
indices=find(changes);
data_points = (0:(size(indices,1)-1))'*60;
start=indices(1);
indices=indices-indices(1);
position=(interp1(indices,data_points,1:indices(end),'linear'))';
figure
time3=0.0002*(0:indices(end)-1);
plot (time3,position)
title('Motor Position')
xlabel('time (s)')
ylabel('position (deg)')
delta_position=diff(position);
speed_rpm=(delta_position/0.0002)/6;
time4=0.0002*(1:size(speed_rpm,1));
rsSpeed= resample(speed_rpm,time4);
rsTime=linspace(time4(1),time4(end),numel(rsSpeed))';
df=designfilt('lowpassiir','FilterOrder',3,'HalfPowerFrequency',0.0007);
ff=filtfilt(df,rsSpeed);
figure
plot(time4,speed_rpm,rsTime,ff)
title('Motor speed')
xlabel('time (s)')
ylabel('speed (RPM)')
legend('unfiltered','filtered')
accel = diff(ff)/0.0002;
accel = cat(1,accel(1),accel);
torque = 1.29*10^(-4)*accel;
figure
plot(ff,torque)
title('speed-torque curve')
xlabel('speed (RPM)')
ylabel('torque (Nm)')
current_short=RMS_current(start:end-19);
figure
plot(current_short,torque)
title('current-torque')
xlabel('current (A)')
ylabel('torque (Nm)')



