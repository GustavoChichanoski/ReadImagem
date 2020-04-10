void add_square_sum ( float in[] , float out[] , const unsigned size ) {
    for (unsigned i = 0; i < size ; i++)
    {
        out[i] += in[i] * in[i] ;
    }
}

void pad(in, out, ih, iw, id, pad)
    const unsigned id, iw, ih, pad;
    float in[], out[];
{
    unsigned oh = ih + 2*pad;
    unsigned ow = iw + 2*pad;
    unsigned d, x, y, o_idx, i_idx;
    for( d = 0; d < id; ++d ) 
    {
        for( y = 0; y < oh; ++y ) 
        {
            for( x = 0; x < ow; ++x ) 
            {
                o_idx = ( oh*d + y ) * ow + x ;
                i_idx = 0;
                if( y < pad || y > ( ih + pad - 1) || x < pad || x > ( iw + pad - 1) ) 
                {
                    out[o_idx] = 0.0;
                } else {
                    i_idx = ( ih * d + y - pad ) * iw + x - pad;
                    out[o_idx] = in[i_idx];
                }
            }
        }
    }
}
