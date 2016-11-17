// ADDITION
BigInt BigInt::addChunks(SuperArray larger, SuperArray smaller, bool same_size){
    BigInt result = BigInt(larger.Length() + 1);
    SuperArray* result_ptr = result.GetSuperArray();
    int carry = 0;
    for(int i = 0; i < smaller.Length(); i++){
        unsigned int temp_num = smaller.Get(i) + larger.Get(i);

        if(carry > 0){
            temp_num += carry;
            carry = 0;
        }

        if(temp_num >= base){
            carry = 1;
            temp_num = temp_num % base;
        }
        (*result_ptr).Push(temp_num);
    }

    if(!same_size){
        for(int i = smaller.Length(); i < larger.Length(); i++){
            unsigned int temp_num = larger.Get(i);

            if(carry > 0){
                temp_num += carry;
            }

            (*result_ptr).Push(temp_num);
        }
    }else if(carry > 0){
        (*result_ptr).Push(carry);
    }
    return result;
}

BigInt BigInt::Add(BigInt input2){
    SuperArray other_array = *input2.GetSuperArray();
    if(other_array.Length() == value.Length()){
        return addChunks(other_array, value, true);
    }else if(other_array.Length() > value.Length()){
        return addChunks(other_array, value, false);

    } else {
        return addChunks(value, other_array, false);
    }
}


// SUBTRACTION
// This function requires the BigInt b is smaller than implied BigInt
SuperArray BigInt::SubtractSmallerFromLarger(BigInt big_int){
    // get them all as SuperArray's, because that is easier to work with
    SuperArray a = this->GetValue();
    // a.Print();
    SuperArray b = big_int.GetValue();
    // b.Print();
    SuperArray c = SuperArray(a.Length()); // c will need just as much memory as the larger SuperArray

    // this is our index, it will go through two for loops
    int i = 0;

    // cout << a.Get(0) << endl;
    // cout << b.Length() << endl;

    // keep in mind b is smaller
    for(; i < b.Length(); i++){ // loop through b, b is smaller
        if (a.Get(i) < b.Get(i)){ // if a - b would result in a negative, you have to borrow
            // cout << a.Get(i) << " " << b.Get(i) << endl;
            a.Borrow(i);
            // c.IncreaseReal();
            c.Set(i, a.Get(i) - b.Get(i));
            // c.Print();
        } else { // if a >= b you do not have to borrow
            // cout << a.Get(i) << " " << b.Get(i) << endl;
            c.Set(i, a.Get(i) - b.Get(i));
            // cout << c.Get(i) << endl;
        }
    }

    for(; i < a.Length(); i++){ // loop through the rest of a, and add it to return
        c.Set(i, a.Get(i));
    }

    c.UpdateSize();
    return c;
}

// for now, both bigints must be positive
BigInt BigInt::Subtract(BigInt b){

    BigInt c = BigInt(); // intialize, proper memory will be allocated later
    BigInt a = *this;

    if(GreaterOrEqual(a, b)){ // if this is greater than b
        c.SetSign(true); // if this >= b then the value will be positive
        c.value = a.SubtractSmallerFromLarger(b);
    } else {  // if this is less than b
        c.SetSign(false); // if this < b then value will be negative
        c.value = b.SubtractSmallerFromLarger(a);
    }

    return c;

}


//////////////
// DIVISION //
//////////////

// a.Divide(b) == a/b

BigInt BigInt::DivideByTwo() {
    /*
     * I feel the need to apologize for this function. We can't figure out why this
     * works and we've spent literally 3 hours on this one bug. That no longer
     * seems to be a problem. God forgive us.
     */

    int remain = 0;
    unsigned int apple;
    int sol;
    bool skip_first = false;

    int allocate_space = value.Length();
    if(value.Get(value.Length() - 1) == 1) {
        skip_first = true;
    }

    SuperArray new_num = SuperArray(allocate_space);

    for(int i = value.Length() - 1; i >= 0; i--) {
        if(remain) {
            apple = value.Get(i) + BigInt::GetBase();
        } else {
            apple = value.Get(i);
        }

        remain = apple % 2;
        sol = apple / 2;

        if(i >= 0 && !skip_first) {
            new_num.Set(i, sol);
            new_num.IncreaseReal();
        }
        skip_first = false;
    }

    BigInt result = BigInt();
    result.SetValue(new_num);
    return result;
}

unsigned int BigInt::FactorDifference(BigInt other) {
    unsigned int our_data_len = value.Length();
    unsigned int other_data_len = other.GetValue().Length();
    unsigned int our_first_chunk_len = to_string(value.Get(our_data_len - 1)).length();
    unsigned int other_first_chunk_len = to_string(other.GetValue().Get(other_data_len - 1)).length();
    unsigned int our_scale = (our_data_len * chunk_size) + our_first_chunk_len;
    unsigned int other_scale = (other_data_len * chunk_size) + other_first_chunk_len;
    if(other_scale > our_scale) {
        return other_scale - our_scale;
    } else {
        return our_scale - other_scale;
    }
}

BigInt BigInt::NextBinaryFinder(BigInt upper_bound) {
    // Call this on the lower bound only pls when transfering this to the division file
    // change it to NextBinaryFinder(BigInt lower_bound, BigInt upper_bound);

    BigInt range = Subtract(upper_bound, *this);
    BigInt half_range = range.DivideByTwo();
    BigInt new_coeff = Add(*this, half_range);
    return new_coeff;
}

BigInt BigInt::LargestMultipleUnderOther(BigInt other) {
    BigInt one = BigInt("1");
    BigInt zero = BigInt("0");

    if(BigIntCompare(*this, other) == 1) {
        return zero;
    }

    unsigned int factor_diff = this->FactorDifference(other);

    cout << factor_diff << endl;

    BigInt lower_coeff = BigInt("0");
    BigInt upper_coeff = BigInt("1");

    for(int i = 0; i < factor_diff + 1; i++) {
        upper_coeff = Multiply(upper_coeff, 10, 0);
    }

    BigInt coeff = lower_coeff.NextBinaryFinder(upper_coeff);

    BigInt diff_of_coeffs = Subtract(upper_coeff, lower_coeff);

    int iterations = 0;

    /*cout << "lower_coeff = " << lower_coeff << endl;
    cout << "upper_coeff = " << upper_coeff << endl;
    cout << "coeff =       " << coeff << endl;*/

    while(BigIntCompare(diff_of_coeffs, one)) {
        iterations++;
        BigInt curr_val = Product(*this, coeff);
        switch(BigIntCompare(curr_val, other)) {
            case 0:
                return coeff;
                break;
            case 1:
                upper_coeff = coeff;
                coeff = lower_coeff.NextBinaryFinder(upper_coeff);
                break;
            case -1:
                lower_coeff = coeff;
                coeff = lower_coeff.NextBinaryFinder(upper_coeff);
                break;
        }

        /*cout << "lower_coeff = " << lower_coeff.ToString() << endl;
        cout << "upper_coeff = " << upper_coeff.ToString() << endl;
        cout << "coeff =       " << coeff.ToString() << endl;*/
        BigInt diff_of_coeffs = Subtract(upper_coeff, lower_coeff);
        //cout << coeff << endl;
        cout << "";
        if(BigIntCompare(diff_of_coeffs, one) < 1) {
            cout << "iterations to find answer = " << iterations << endl;
            return coeff;
        }
        //cin.ignore();
    }
    return coeff;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //
//                                                                            //
// Remove the arithmetic functions when move to seperate modules are complete //
//                                                                            //
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //

//////////////
// ADDITION //
//////////////

/*BigInt BigInt::addChunks(SuperArray larger, SuperArray smaller, bool same_size){
    BigInt result = BigInt(larger.Length() + 1);
    SuperArray* result_ptr = result.GetSuperArray();
    int carry = 0;
    for(int i = 0; i < smaller.Length(); i++){
        unsigned int temp_num = smaller.Get(i) + larger.Get(i);

        if(carry > 0){
            temp_num += carry;
            carry = 0;
        }

        if(temp_num >= base){
            carry = 1;
            temp_num = temp_num % base;
        }
        (*result_ptr).Push(temp_num);
    }

    if(!same_size){
        for(int i = smaller.Length(); i < larger.Length(); i++){
            unsigned int temp_num = larger.Get(i);

            if(carry > 0){
                temp_num += carry;
            }

            (*result_ptr).Push(temp_num);
        }
    }else if(carry > 0){
        (*result_ptr).Push(carry);
    }
    return result;
}*/

/*BigInt BigInt::Add(BigInt input2){
    SuperArray other_array = *input2.GetSuperArray();
    if(other_array.Length() == value.Length()){
        return addChunks(other_array, value, true);
    }else if(other_array.Length() > value.Length()){
        return addChunks(other_array, value, false);

    } else {
        return addChunks(value, other_array, false);
    }
}*/

/////////////////
// SUBTRACTION //
/////////////////

// This function requires the BigInt b is smaller than implied BigInt
/*SuperArray BigInt::SubtractSmallerFromLarger(BigInt big_int){
    // get them all as SuperArray's, because that is easier to work with
    SuperArray a = this->GetValue();
    // a.Print();
    SuperArray b = big_int.GetValue();
    // b.Print();
    SuperArray c = SuperArray(a.Length()); // c will need just as much memory as the larger SuperArray

    // this is our index, it will go through two for loops
    int i = 0;

    // cout << a.Get(0) << endl;
    // cout << b.Length() << endl;

    // keep in mind b is smaller
    for(; i < b.Length(); i++){ // loop through b, b is smaller
        if (a.Get(i) < b.Get(i)){ // if a - b would result in a negative, you have to borrow
            // cout << a.Get(i) << " " << b.Get(i) << endl;
            a.Borrow(i);
            // c.IncreaseReal();
            c.Set(i, a.Get(i) - b.Get(i));
            // c.Print();
        } else { // if a >= b you do not have to borrow
            // cout << a.Get(i) << " " << b.Get(i) << endl;
            c.Set(i, a.Get(i) - b.Get(i));
            // cout << c.Get(i) << endl;
        }
    }

    for(; i < a.Length(); i++){ // loop through the rest of a, and add it to return
        c.Set(i, a.Get(i));
    }

    c.UpdateSize();
    return c;
}*/



////////////////////
// MULTIPLICATION //
////////////////////


/*BigInt BigInt::Multiply(int input, int shift_ammount){
    SuperArray answer_so_far = SuperArray();
    for (int i = 0; i < shift_ammount; i++){
        answer_so_far.Push(0);
    }
    int carry_over = 0;
    for (int i=0; i<this->GetValue().Length(); i++){
        int val = this->GetValue().Get(i);
        val *= input;
        val += carry_over;
        carry_over = val / GetBase(); // front digits
        val = val % GetBase(); // last base digits

        answer_so_far.Push(val);
    }
    if (carry_over > 0){
        answer_so_far.Push(carry_over);
    }
    BigInt answer = BigInt();
    answer.value = answer_so_far;
    return answer;
}*/