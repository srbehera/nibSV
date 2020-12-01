1. Simulate SV

	SURVIVOR simSV testNib_seq.fa parameter_file 0.1 0 out
	(Output files: out.vcf, out.bed, out.fasta, out.insertion.fasta)

2. Generate illumina reads

	(from modified fasta i.e. out.fasta using read length(n) = 150bp, paired end(mp), Total # reads: 350 (for 10x coverage))

	mason illumina -n 150 -N 350 -mp out.fasta

3. Map the reads to reference (using BWA)

	bwa index testNib_seq.fa
	bwa mem testNib_seq.fa out.fasta_1.fasta out.fasta_2.fasta > out.sam
 
4. Convert sam to bam, sort bam and generate cram
 
	samtools view -bS out.sam > out.bam
	samtools sort out.bam > out_sorted.bam
	samtools view -T testNib_seq.fa -C -o out.cram out_sorted.bam
 
5. Run nibblerSV
 
	src/nibsv main -v out.vcf -r testNib_seq.fa --reads-fn out.cram -p test
