#include "test_runner.h"

struct Nucleotide {
  char Symbol;
  size_t Position;
  int ChromosomeNum;
  int GeneNum;
  bool IsMarked;
  char ServiceInfo;
};


struct CompactNucleotide {
  uint32_t position;
  uint32_t symbol : 2;
  uint32_t chromosome_num : 6;
  uint32_t gene_num : 15;
  uint32_t is_marked : 1;
  uint32_t service_info : 8;
};


bool operator == (const Nucleotide& lhs, const Nucleotide& rhs);

CompactNucleotide Compress(const Nucleotide& n);

Nucleotide Decompress(const CompactNucleotide& cn);

void TestSize() {
  ASSERT(sizeof(CompactNucleotide) <= 8);
}

void TestCompressDecompress() {
  Nucleotide source;

  source.Symbol = 'T';
  source.Position = 1'000'000'000;
  source.ChromosomeNum = 48;
  source.GeneNum = 1'000;
  source.IsMarked = true;
  source.ServiceInfo = 'Test';

  CompactNucleotide compressedSource = Compress(source);
  Nucleotide decompressedSource = Decompress(compressedSource);

  ASSERT(source == decompressedSource);
}

int main() {
  TestRunner tr;
  cout << sizeof(Nucleotide) << endl << sizeof(CompactNucleotide) << endl;

  RUN_TEST(tr, TestSize);
  RUN_TEST(tr, TestCompressDecompress);

  return 0;
}
