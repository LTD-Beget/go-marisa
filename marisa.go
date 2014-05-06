package marisa

// #include "cmarisa.h"
// #include <stdlib.h>
// #cgo LDFLAGS: -lmarisa
import "C"
import "runtime"
import "unsafe"

type KeySet struct {
	keyset *C.KeySet
}

type Trie struct {
	trie *C.Trie
}

// KeySet
func NewKeySet() *KeySet {
	self := &KeySet{C.keyset_create()}
	runtime.SetFinalizer(self, (*KeySet).free)
	return self
}

func (self *KeySet) free() {
	C.keyset_destroy(self.keyset)
}

func (self *KeySet) Push(s string, weight int) {
	cs := C.CString(s)
	l := len(s)
	C.keyset_push(self.keyset, cs, C.int(l), C.int(weight))
	C.free(unsafe.Pointer(cs))
}

// Trie
func NewTrie() *Trie {
	self := &Trie{C.trie_create()}
	runtime.SetFinalizer(self, (*Trie).free)
	return self
}

func (self *Trie) free() {
	C.trie_destroy(self.trie)
}

func (self *Trie) Build(ks KeySet, flags int) {
	C.trie_build(self.trie, ks.keyset, C.int(flags))
}

func (self *Trie) Save(path string) {
	cpath := C.CString(path)
	C.trie_save(self.trie, cpath)
	C.free(unsafe.Pointer(cpath))
}
