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

% Run 2 identical simulations to check reproducibility
for i = 1:2
    umod = schnakenberg(umod);
    umod.vol = 50/mean(umod.vol)*umod.vol;
    umod.D = sparse(zeros(size(umod.D)));
    umod.solver = 'ssa';
    umod.makeargs = {'openmp', true};
    umod.solverargs = {'threads', nthreads};
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

    % save results
    if(i==1)
        firstresults = umod.U;
    elseif (i==2)
        secondresults = umod.U; 
    end
end

% Check if results are consistent
if(firstresults == secondresults)
    disp('experiment successful');
else
    disp('experiment failed');
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

% Run 2 identical simulations to check reproducibility
for i = 1:2
    vmod.sd = ceil(vmod.sd);
    vmod = brusselator(vmod);
    vmod.vol = 100/mean(vmod.vol)*vmod.vol;
    vmod.D = sparse(zeros(size(vmod.D)));
    vmod.solver = 'ssa';
    vmod.solverargs = {'threads', nthreads};
    vmod.makeargs = {'openmp', true};
    vmod.rng = rng;
    vmod.seed = 1:replicas;

    % Create more replicas if specified
    if(replicas > 1)
        copy = vmod.u0;
        for r = 1:replicas-1
            vmod.u0 = cat(3, vmod.u0, copy);
        end
    end

    % solve
    vmod = urdme(vmod,'report',0);

    % save results
    if(i==1)
        firstresults = umod.U;
    elseif (i==2)
        secondresults = umod.U; 
    end
end

% Check if result are consistent
if(firstresults == secondresults)
    disp('experiment successful');
else
    disp('experiment failed');
end


