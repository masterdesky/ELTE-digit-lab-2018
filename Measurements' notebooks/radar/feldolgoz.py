from numpy import convolve, mean, sin, pi
from pylab import find

def radar_korkep(fn, dphi = .015, s_chirp = 9.5, n_chirp = 3, noise_percentile = .99, trig_thresh = .8, cut_sample = .75):
    """
param fn: filename (*.wav)
param dphi: egy lepes
param trig_thresh: simitott trigger maximumkeresesi parametere
param cut_sample: az atlagos minta hossz hanyad reszet tartsuk meg
param s_chirp: a csirip periodusideje mintaszamban
param n_chirp: hany hullam fer egy csomagba
param noise_percentile: zaj teteje
return adatsor [(szog, tav, intenzitas), ]
    """
    v = 343                                # v: ultrahang terjedesi sebessege cirka [m/s]
    r0 = 1.2                               # r0: 2*jelado-tukor tavolsag + egy kicsi [m]
    import scipy.io.wavfile
    #fs: mintaveteli gyakorisag [Hz]
    #D: stereo minta, elso csatorna pendites, masodik csatorna detektalt jel
    [fs, D] = scipy.io.wavfile.read(fn)
    D = D.T                                # transzponaljuk a kezelhetoseg erdekeben
    # az elso sor a pendites jele
    # hatarozzuk meg ezeknek a kezdetet, (a lefele uteseket)
    # simitsunk 3 egymas utani jelet es kepezzuk a differenciat: [1 1 1] [1 -1] konvolvatja [1 0 0 -1]
    Dd = convolve(D[0], [-1, 0, 0, 1])
    pos_naive = find( Dd > trig_thresh * max(Dd) )
    # finomitsuk az indexeket, az egymas utani talalatokat olvasszuk egybe
    old = -1
    pos = []
    for p in pos_naive:
        if old+1 != p:
            pos.append(p - 2)               # a convolve kicsit feltol, es amúgy sem art FIXME: pos<1 eldobni
        old = p
 
    # mintahossz: a penditesek kozott eltelt tipikus mintaszam
    mintahossz = cut_sample * mean(convolve(pos, [1,-1])[:-1])
    print("Mintaszam:\t%d\nMintahossz:\t%f\n" % (len(pos), mintahossz))

    # a jelet allitsuk az atlaga kore (DC offszet kiszedese)
    Sac = D[1] - mean(D[1])
    # az ultrahang minta elejen a kimeno + tukorrol visszaverodo jel nem hordoz szamunkra hely-informaciot, kiszurjuk.
    cutrange = int(fs*r0/v)
    for p in pos:
        Sac[p:p+cutrange] = 0

    # keressunk sinusos mintazatot
    csomag = [ sin(2*pi*x/s_chirp) for x in range(int(n_chirp * s_chirp)) ]
    Jc = convolve(Sac, csomag) ** 2

    # nyomjuk el a zajt
    Jccopy = Jc.copy()
    Jccopy.sort()
    noise_thresh = Jccopy[int(noise_percentile * len(Jc))]
    print("A zaj vagasa: %f\n" % noise_thresh)
    Jc[find(Jc <= noise_thresh)] = 0
    del Jccopy

    # rendeljunk intenzitas erteket a visszavert jelhez es hatarozzuk meg a helyet
    INT = []
    for p in pos:
        myslice = Jc[p:p+int(mintahossz)]
        signalstren = sum(myslice)
        if signalstren > 0:
            place = min(find(myslice > 0))
            INT.append( (dphi * p / mintahossz, place, signalstren) )
    return INT