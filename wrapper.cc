#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <marisa.h>

extern "C" {
	struct KeySet {
		marisa::Keyset *keyset;
	};
	struct Trie {
		marisa::Trie   *trie;
	};
	struct Key {
		const marisa::Key 	*key;
	};
	struct Agent {
		marisa::Agent 	*agent;
	};

	KeySet *keyset_create(void) {
		KeySet *ks = (KeySet*)malloc(sizeof(KeySet));

		ks->keyset = new(marisa::Keyset);
		return ks;
	}

	void keyset_push(KeySet *ks, const char *str, int len, int value) {
		ks->keyset->push_back(str, len, value);
	}

	void keyset_destroy(KeySet *ks) {
		delete(ks->keyset);
		ks->keyset = NULL;
	}

	Trie *trie_create(void) {
		Trie *t = (Trie*)malloc(sizeof(Trie));

		t->trie = new(marisa::Trie);
		return t;
	}

	void trie_build(Trie *tr, KeySet *ks, int options) {
		tr->trie->build(*ks->keyset, options);
	}

	void trie_save(Trie *tr, const char *filename) {
		tr->trie->save(filename);
	}

	void trie_mmap(Trie *tr, const char *filename) {
		tr->trie->mmap(filename);
	}

	Agent *agent_create(void) {
		Agent *a = (Agent*)malloc(sizeof(Agent));

		a->agent = new(marisa::Agent);

		return a;
	}

	void set_query(Agent *a, const char *q) {
		a->agent->set_query(q);
	}

	Key *get_key(Agent *a) {
		Key *k = (Key*)malloc(sizeof(Key));
		k->key = &a->agent->key();

		return k;
	}

	const char *get_value(Key *k) {
		return k->key->ptr();
	}

	bool predictive_search(Trie *t, Agent *a) {
		t->trie->predictive_search(*a->agent);
	}

}
