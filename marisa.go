package marisa
// #include "cmarisa.h"
// #cgo LDFLAGS: -lmarisa
import "C"

type KeySet struct {
	keyset *C.KeySet
}

type Trie struct {
	trie *C.Trie
}

// KeySet
func NewKeySet() (self KeySet) {
	self.keyset = C.keyset_create()
	return
}

func (self *KeySet) Push(s string, weight int) {
	cs := C.CString(s)
	l := len(s)
	C.keyset_push(self.keyset, cs, C.int(l), C.int(weight))
}

func (self *KeySet) Free() {
    C.keyset_destroy(self.keyset)
}

// Trie
func NewTrie() (self Trie) {
	self.trie = C.trie_create()
	return
}

func (self *Trie) Build(ks KeySet, flags int) {
	C.trie_build(self.trie, ks.keyset, C.int(flags))
}

func (self *Trie) Save(path string) {
	cpath := C.CString(path)
	C.trie_save(self.trie, cpath)
}
