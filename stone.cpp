#include <vector>
#include "stone.hpp"
#include "goban.hpp"
#include "intersection.hpp"
#include "chain.hpp"
#include "exception.hpp"

Stone::Stone(Intersection* iPtr, bool black) : chain_(0), iPtr_(iPtr), libs(8), black_(black) {
	icon_ = black ? 'X' : 'O';
	connectToNeighbours();
	seeIfAnyoneIsDead();
}

Stone::~Stone() {
	iPtr_->goban_->noteStoneRemoval(iPtr_, black_);
	iPtr_->stone_ = 0;
	if (chain_) {
		chain_->removeStone(this);
		chain_->considerDying();
	}
	increaseNeighbourLiberties();
}

char Stone::getIcon() {
	return icon_;
}

void Stone::connectToNeighbours() {
	connectTo(iPtr_->nbr_->up);
	connectTo(iPtr_->nbr_->down);
	connectTo(iPtr_->nbr_->left);
	connectTo(iPtr_->nbr_->right);
	connectTo(iPtr_->nbr_->farup);
	connectTo(iPtr_->nbr_->fardown);
	connectTo(iPtr_->nbr_->farleft);
	connectTo(iPtr_->nbr_->farright);
	if (!chain_)
		chain_ = new Chain(this);
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
	giveLiberty(iPtr_->nbr_->up);
	giveLiberty(iPtr_->nbr_->down);
	giveLiberty(iPtr_->nbr_->left);
	giveLiberty(iPtr_->nbr_->right);
	giveLiberty(iPtr_->nbr_->farup);
	giveLiberty(iPtr_->nbr_->fardown);
	giveLiberty(iPtr_->nbr_->farleft);
	giveLiberty(iPtr_->nbr_->farright);
}

void Stone::giveLiberty(Intersection* p) {
	if (!p)
		return;
	if (!p->stone_)
		return;
	++(p->stone_->libs);
}

void Stone::seeIfAnyoneIsDead() {
	std::vector<Chain*> enemyChains;
	getChain(enemyChains, iPtr_->nbr_->up);
	getChain(enemyChains, iPtr_->nbr_->down);
	getChain(enemyChains, iPtr_->nbr_->left);
	getChain(enemyChains, iPtr_->nbr_->right);
	getChain(enemyChains, iPtr_->nbr_->farup);
	getChain(enemyChains, iPtr_->nbr_->fardown);
	getChain(enemyChains, iPtr_->nbr_->farleft);
	getChain(enemyChains, iPtr_->nbr_->farright);
	for (uint i = 0; i < enemyChains.size(); ++i)
		enemyChains[i]->considerDying();
	chain_->considerDying(true);
}

void Stone::getChain(std::vector<Chain*>& chvec, Intersection* p) {
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
