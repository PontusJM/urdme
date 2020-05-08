% RESULT DISPLAY %

close all;

% RNG impact &
% DRAND48, RAND_R, GSL_TAUS2, GSL_MT19937, GSL_RANLXS0, GSL_RANXLS2 %
rng =  [142.099, 58.337, 58.468, 59.577, 67.681, 112.612];
bar(rng,0.5);
ylabel('time [s]');
title('Execution times for RNG algorithms');
set(gca, 'XTickLabel', {'DRAND48', 'RAND\_R', 'GSL\_TAUS2', 'GSL\_MT19937', 'GSL\_RANLXS0', 'GSL\_RANLXS2'});

% Task Based MT19937 performance vs. serial 12 replicas %
% 1 2 4 6 8 10 12 %
mt = [491.197, 267.168 , 176.913, 174.847, 162.753, 191.435, 144.203];
bar(mt,0.5);
ylabel('time [s]')
title('Execution times of the task based parallel solver compared to the serial solver');
set(gca,'XTickLabel',{1,2,4,6,8,10,12});
hold on
plot(xlim,[457.561 457.561], 'r')
legend({'Parallel','Serial'});


% Task Based MT19937 performance vs. serial 6 replicas %
% 1 2 4 6 8 10 12 %
mt = [243.456, 132.936 , 104.158 , 87.548 , 87.750, 87.350, 87.350];
bar(mt,0.5);
ylabel('time [s]')
title('Execution times of the task based parallel solver compared to the serial solver');
set(gca,'XTickLabel',{1,2,4,6,8,10,12});
hold on
plot(xlim,[221.623 221.623], 'r')
legend({'Parallel','Serial'});


% Task Based MT19937 performance vs. serial 1 replica %
% 1 2 4 6 8 10 12 %
mt = [40.587, 40.691 , 40.697, 40.675, 40.614, 40.595 , 40.578];
bar(mt,0.5);
ylabel('time [s]')
title('Execution times of the task based parallel solver compared to the serial solver');
set(gca,'XTickLabel',{1,2,4,6,8,10,12});
hold on
plot(xlim,[39.578 39.578], 'r')
legend({'Parallel','Serial'});