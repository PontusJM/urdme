%Morphogenesis 2D script file.
%   This file runs the Schnakenberg and the Brusselator models in
%   simple 2D geometries.
%
%   Reference:
%     [1] Y. Saygun: "Computational Stochastic Morphogenesis", MSc
%     thesis in Engineering Physics, Uppsala university (2015).

% P. Melin 2020-05-22
% S. Engblom 2017-03-08


% threading options (pontus)
nthreads = 8;
replicas = 1;
rng = 'GSL_MT19937';


%% (1) Schnakenberg

disp(strcat('Running with ',rng, ' threads: ', string(nthreads)));

% build the geometry
C1 = [1 0 0 50]';
C2 = [1 0 0 15]';
gd = [C1 C2];
sf = 'C1-C2';
ns = char('C1','C2')';
G = decsg(gd,sf,ns);

% create the mesh
[P,E,T] = initmesh(G,'hmax',2.5);

% assemble the diffusion part
D_U = 1;
D_V = 40;
clear umod
umod = pde2urdme(P,T,{D_U D_V});
if exist('tspan','var')
  umod.tspan = tspan;
end
  
% not used
umod.sd = ceil(umod.sd);

if ~exist('plotting_off','var') || ~plotting_off
  figure(1), clf,
  pdegplot(G,'subdomainlabels','on'), axis equal

  figure(2), clf,
  pdemesh(P,E,T), axis tight, axis equal
end
  
umod = schnakenberg(umod);
umod.vol = 50/mean(umod.vol)*umod.vol;
umod.D = sparse(zeros(size(umod.D)));
umod.solver = 'ssa';
umod.makeargs = {'openmp', true, 'nthreads', nthreads};
umod.rng = rng;
umod.seed = 1:replicas;

% Create more replicas if specified
if(replicas > 1)
    copy = umod.u0;
    for r = 1:replicas-1
    umod.u0 = cat(3, umod.u0, copy);
    end
end

% solve
umod = urdme(umod,'report',0);

% visualize using PDE Toolbox
umod = urdme2pde(umod);
if ~exist('plotting_off','var') || ~plotting_off
  figure(3), clf,
  pdesurf(umod.pde.P,umod.pde.T,umod.pde.U(1,:,end)');
  title('Schnakenberg: Concentration U');
  view(0,90), axis tight, axis square, colormap('parula')
  figure(4), clf,
  h = pdesurf(umod.pde.P,umod.pde.T,umod.pde.U(2,:,end)');
  title('Schnakenberg: Concentration V');
  view(0,90), axis tight, axis square, colormap('parula')
end

%% (2) Brusselator
% build the geometry
C1 = [1 0 0 25]';
gd = [C1];
sf = 'C1';
ns = char('C1')';
G = decsg(gd,sf,ns);

% create the mesh
[P,E,T] = initmesh(G,'hmax',2);

% assemble the diffusion part
D_U = 2;
D_V = 16;
clear vmod
vmod = pde2urdme(P,T,{D_U D_V});
if exist('tspan','var')
  vmod.tspan = tspan;
end

vmod.sd = ceil(vmod.sd);
vmod = brusselator(vmod);
vmod.vol = 100/mean(vmod.vol)*vmod.vol;
vmod.D = sparse(zeros(size(vmod.D)));
vmod.solver = 'ssa';
vmod.makeargs = {'openmp', true, 'nthreads', nthreads};
vmod.rng = rng;
vmod.seed = 1:replicas;

if(replicas > 1)
    copy = vmod.u0;
    for r = 1:replicas-1
    vmod.u0 = cat(3, vmod.u0, copy);
    end
end

%solve
vmod = urdme(vmod,'report',0);
   
% visualize using PDE Toolbox
vmod = urdme2pde(vmod);
if ~exist('plotting_off','var') || ~plotting_off
  figure(5), clf,
  pdesurf(vmod.pde.P,vmod.pde.T,vmod.pde.U(1,:,end)');
  title('Brusselator: Concentration U');
  view(0,90), axis tight, axis square, colormap('parula')
  figure(6), clf,
  pdesurf(vmod.pde.P,vmod.pde.T,vmod.pde.U(2,:,end)');
  title('Brusselator: Concentration V');
  view(0,90), axis tight, axis square, colormap('parula')
end

% possibly print to files

figure(2),
set(gcf,'PaperPositionMode','auto');
set(gcf,'Position',[100 100 380 250]);
%print -depsc  ../../doc/fig/Schnakenberg_mesh.eps

figure(3),
set(gcf,'PaperPositionMode','auto');
set(gcf,'Position',[100 100 380 250]);
%print -depsc  ../../doc/fig/Schnakenberg.eps
