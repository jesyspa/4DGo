#include <vector>
#include <server/stone.hpp>
#include <server/goban.hpp>
#include <server/intersection.hpp>
#include <server/chain.hpp>
#include <exceptions.hpp>

namespace fdgo {
namespace server {

Stone::Stone(Intersection* intrPtr, bool black) : intrPtr_(intrPtr), libs(8), black_(black) {
	connectToNeighbours();
	seeIfAnyoneIsDead();
}

Stone::~Stone() {
	intrPtr_->goban_->noteStoneRemoval(intrPtr_, black_);
	increaseNeighbourLiberties();
	intrPtr_->stone_ = 0;
	if (chain_) {
		chain_->removeStone(this);
	}
}

void Stone::connectToNeighbours() {
	connectTo(intrPtr_->nbr_->up);
	connectTo(intrPtr_->nbr_->down);
	connectTo(intrPtr_->nbr_->left);
	connectTo(intrPtr_->nbr_->right);
	connectTo(intrPtr_->nbr_->farup);
	connectTo(intrPtr_->nbr_->fardown);
	connectTo(intrPtr_->nbr_->farleft);
	connectTo(intrPtr_->nbr_->farright);
	if (!chain_)
		chain_.reset(new Chain(this));
}

void Stone::connectTo(Intersection* p) {
	if (!isSameColour(p))
		return;
	if (chain_) {
		if (chain_ == p->stone_->chain_)
			return;
		p->stone_->chain_->joinWith(chain_);
	} else {
		p->stone_->chain_->addStone(this);
	}
	
}

bool Stone::isSameColour(Intersection* p) {
	if (!p) {
		--libs;
		return false;
	}
	if (!p->stone_)
		return false;
	--libs;
	--(p->stone_->libs);
	return p->stone_->black_ == black_;
}

void Stone::increaseNeighbourLiberties() {
	giveLiberty(intrPtr_->nbr_->up);
	giveLiberty(intrPtr_->nbr_->down);
	giveLiberty(intrPtr_->nbr_->left);
	giveLiberty(intrPtr_->nbr_->right);
	giveLiberty(intrPtr_->nbr_->farup);
	giveLiberty(intrPtr_->nbr_->fardown);
	giveLiberty(intrPtr_->nbr_->farleft);
	giveLiberty(intrPtr_->nbr_->farright);
}

void Stone::giveLiberty(Intersection* p) {
	if (!p)
		return;
	if (!p->stone_)
		return;
	++(p->stone_->libs);
}

void Stone::seeIfAnyoneIsDead() {
	std::vector<Chain::Pointer> enemyChains;
	getChain(enemyChains, intrPtr_->nbr_->up);
	getChain(enemyChains, intrPtr_->nbr_->down);
	getChain(enemyChains, intrPtr_->nbr_->left);
	getChain(enemyChains, intrPtr_->nbr_->right);
	getChain(enemyChains, intrPtr_->nbr_->farup);
	getChain(enemyChains, intrPtr_->nbr_->fardown);
	getChain(enemyChains, intrPtr_->nbr_->farleft);
	getChain(enemyChains, intrPtr_->nbr_->farright);
	for (uint i = 0; i < enemyChains.size(); ++i)
		enemyChains[i]->considerDying();
	chain_->considerDying(true);
}

void Stone::getChain(std::vector<Chain::Pointer>& chvec, Intersection* p) {
	if (!p)
		return;
	if (!p->stone_)
		return;
	if (p->stone_->black_ == black_)
		return;
	for (uint i = 0; i < chvec.size(); ++i)
		if (p->stone_->chain_ == chvec[i])
			return;
	chvec.push_back(p->stone_->chain_);
}

}
}
