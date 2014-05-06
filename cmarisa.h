typedef struct KeySet {
	void *keyset;
} KeySet;
typedef struct Trie {
	void *trie;
} Trie;
typedef struct Key {
	const void *key;
} Key;
typedef struct Agent {
	void *agent;
} Agent;

KeySet *keyset_create(void);
void keyset_push(KeySet*, const char*, int, int);
void keyset_destroy(KeySet*);

Trie *trie_create(void);
void trie_build(Trie*, KeySet*, int);
void trie_save(Trie*, const char *);
void trie_destroy(Trie*);
void mmap(Trie*, const char *);

Agent *agent_create(void);
void set_query(Agent*, const char*);

Key *get_key(Agent *);
const char *get_value(Key *k);
int predictive_search(Trie *, Agent *);
