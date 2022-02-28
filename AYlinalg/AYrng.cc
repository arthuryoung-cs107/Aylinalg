#include "AYlinalg.hh"
#include <math.h>

extern "C"
{
  #include "AYaux.h"
}

AYrng::AYrng(): carry(lcg_fwd(seed, jump))
{}
AYrng::AYrng(uint64_t seed_)
{seed+=seed_; carry = lcg_fwd(seed, jump);}
AYrng::AYrng(uint64_t seed_, uint64_t jump_): seed(seed_), jump(seed_), carry(lcg_fwd(seed, jump)) {}
AYrng::~AYrng() {}
void AYrng::rng_true_init(uint64_t seed_, uint64_t jump_)
{seed = seed_; jump = jump_; carry = lcg_fwd(seed, jump);}
void AYrng::rng_init(uint64_t seed_)
{seed+=seed_; jump=100; carry=lcg_fwd(seed, jump);}
double AYrng::rand_gen() {return 0.0;}
double AYrng::dseed() {return ((double)seed)/(lcg_sze());}
double AYrng::dcarry() {return ((double)carry)/(lcg_sze());}

AYuniform::AYuniform(double low_, double high_): AYrng(), low(low_), high(high_) {}
AYuniform::AYuniform(double low_, double high_, uint64_t seed_): AYrng(seed_), low(low_), high(high_) {}
AYuniform::~AYuniform(){}
double AYuniform::rand_gen() {return knuth_random_uni(low, high, &carry);}

AYnormal::AYnormal(double mu_, double var_): AYrng(), mu(mu_), var(var_) {}
AYnormal::AYnormal(double mu_, double var_, uint64_t seed_): AYrng(seed_), mu(mu_), var(var_) {}
AYnormal::~AYnormal() {}
double AYnormal::rand_gen()
{return boxmuller_knuth(mu, var, &carry);}
