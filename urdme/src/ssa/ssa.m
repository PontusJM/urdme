function ssa
%SSA URDME Direct Method ("SSA") solver.
%   The URDME SSA solver is a straightforward implementation of
%   Gillespie's "Direct Method [1] for the spatial case assuming no
%   transport processes. The URDME SSA thus implements independent
%   reaction processes in the voxels of the model.
%
%   The parallel SSA solver supports threading, the number of threads can
%   be set through the 'threads' property.
%
%   The SSA solver furhter supports all solver arguments present in NSM, see
%   NSM. Additionally, the SSA solver accepts make arguments, see
%   MEXMAKE_SSA.
%
%   Example:
%     % a dimerization under increasing system volume
%     clear umod;
%     umod.vol = 10.^linspace(0,3,5);
%
%     % no diffusion
%     umod.D = sparse(numel(umod.vol),numel(umod.vol));
%
%     % dimarization model
%     [K,I,N,G] = rparse_inline({'@ > k > X','X+X > nu > @'}, ...
%                               {'X'},{'k' 1e2 'nu' 2e1});
%     umod.N = N;
%     umod.G = G;
%     umod.inline_propensities = struct('K',K,'I',I);
%
%     % subdomain
%     umod.sd = ones(size(umod.vol));
%
%     % initial state u0 and time interval
%     umod.u0 = zeros(size(umod.vol));
%     umod.tspan = linspace(0,1,100);
%     
%     % number of threads to be utilized
%     umod.solverargs = {'threads', 4 }
%     
%     % RNG to be used
%     umod.rng = 'GSL_MT19937'
%
%     % compile and solve...
%     umod = urdme(umod,'solver','ssa');
%     U1 = umod.U;
%
%     % ...compare with the corresponding deterministic model
%     umod = urdme(umod,'solver','uds');
%     U2 = umod.U;
%
%     figure, semilogy(umod.tspan,U1,'b',umod.tspan,U2,'r');
%
%   See also UDS, NSM, RPARSE_INLINE.
%
%   References:
%     [1] D. T. Gillespie: "A general method for numerically
%     simulating the stochastic time evolution of coupled chemical
%     reactions", J. Comput. Phys. 22(4):403--434 (1976).

% S. Engblom 2019-11-27 (Revision, inline propensities)
% S. Engblom 2017-02-22

error('This file should not be called directly.');
