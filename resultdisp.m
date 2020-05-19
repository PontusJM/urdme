% RESULT DISPLAY %

close all;

% RNG impact (task; chunk) &
% DRAND48, RAND_R, GSL_TAUS2, GSL_MT19937, GSL_RANLXS0, GSL_RANXLS2 %
rng =  [142.099, 150.365; 58.337, 61.884; 58.468, 64.028; 59.577, 66.5; 67.681, 78.621; 112.612, 124.408];
bar(rng);
ylabel('time [s]');
title('Execution times of RNG algorithms','FontSize',15);
set(gca, 'XTickLabel', {'DRAND48', 'RAND\_R', 'GSL\_TAUS2', 'GSL\_MT19937', 'GSL\_RANLXS0', 'GSL\_RANLXS2'});
ax = gca;
ax.XAxis.FontSize = 15;
ax.YAxis.FontSize = 15;
legend({'Task','Transparent'},'FontSize',15);
figure;

% Task Based MT19937 performance vs. serial 12 replicas %
% 1 2 4 6 8 10 12 %
res = [491.197 495.404; 267.168 272.454; 176.913 190.74; 174.847 185.078; 162.753 175.078; 191.435 161.318; 144.203 157.896];
bar(res);
ylabel('Time [s]')
xlabel('Threads')
title('Execution times of the different solvers running on a varying amount of threads','FontSize',15);
set(gca,'XTickLabel',{1,2,4,6,8,10,12});
ax = gca;
ax.XAxis.FontSize = 15;
ax.YAxis.FontSize = 15;
hold on
plot(xlim,[457.561 457.561], 'r','LineWidth',2.5)
legend({'Task','Transparent','Serial'},'FontSize',15);

figure;

% Task Based MT19937 performance vs. serial 6 replicas %
% 1 2 4 6 8 10 12 %
res = [243.456 247.845; 132.936 141.238; 104.158 96.743; 87.548 93.382; 87.750 88.726; 87.350 83.07; 87.350 80.051];
bar(res);
ylabel('Time [s]')
xlabel('Threads')
title('Execution times of the different solvers running on a varying amount of threads','FontSize',15);
set(gca,'XTickLabel',{1,2,4,6,8,10,12});
ax = gca;
ax.XAxis.FontSize = 15;
ax.YAxis.FontSize = 15;
hold on
plot(xlim,[221.623 221.623], 'r','LineWidth',2.5)
legend({'Task','Transparent','Serial'},'FontSize',15);

figure;

% Task Based MT19937 performance vs. serial 1 replica %
% 1 2 4 6 8 10 12 %
res = [40.587 42.727; 40.691 24.042; 40.697 15.891; 40.675 15.056; 40.614 14.669; 40.595 13.846; 40.578 13.106];
bar(res);
ylabel('Time [s]')
xlabel('Threads')
title('Execution times of the different solvers running on a varying amount of threads','FontSize',15);
set(gca,'XTickLabel',{1,2,4,6,8,10,12});
ax = gca;
ax.XAxis.FontSize = 15;
ax.YAxis.FontSize = 15;
hold on
plot(xlim,[39.578 39.578], 'r','LineWidth',2.5)
legend({'Task','Transparent','Serial'},'FontSize',15);
